//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
#include "libcli.hxx"

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#define CLITEST_PORT            8000
#define MODE_CONFIG_INT         10

#ifdef __GNUC__
# define UNUSED(d) d __attribute__ ((unused))
#else
# define UNUSED(d) d
#endif

using namespace LIBCLI;
using namespace std;

class my_cli : public CLI
{
public:
	void setup();
	int  check_auth (const string& username, const string& password);
	int  check_enable(const string& password);

private:
	int test (char *command, char *argv[], int argc);
};

int  my_cli::check_auth (const string& username, const string& password)
{
	if (username != "x")
		return -1;
	if (password != "x")
		return -1;
	return LIBCLI::OK;
}

int my_cli::check_enable(const string& password)
{
	return (password == "x");
}

void my_cli::setup()
{
	typedef Command<CLI>::cpp_callback_func callback_ptr;
	typedef CLI::cpp_auth_func auth_callback;
	typedef CLI::cpp_enable_func enable_callback;
	Command<CLI>* c;
	Command<CLI>* c2;

	set_auth_callback( static_cast<auth_callback> (& my_cli::check_auth) );
	set_enable_callback( static_cast<enable_callback> (& my_cli::check_enable) );
	
	
	c = new Command<CLI> (
		this,
		"show",
		LIBCLI::UNPRIVILEGED,
		LIBCLI::MODE_ANY,
		"Show running system information"
	);
	register_command (c);

	register_command ( new Command<CLI> (
		this,
		"version",
		static_cast<callback_ptr> (&my_cli::test),
		LIBCLI::UNPRIVILEGED,
		LIBCLI::MODE_ANY,
		"Show version information"
	), c);

	c2 = new Command<CLI> (
		this,
		"blacklist",
		static_cast<callback_ptr> (&my_cli::test),
		LIBCLI::UNPRIVILEGED,
		LIBCLI::MODE_ANY,
		"Show list"
	);
	register_command (c2, c);

	register_command ( new Command<CLI> (
		this,
		"brief",
		static_cast<callback_ptr> (&my_cli::test),
		LIBCLI::UNPRIVILEGED,
		LIBCLI::MODE_ANY,
		"Show list brief"
	), c2);
}

int my_cli::test (char *command, char *argv[], int argc)
{
	print ("called %s with \"%s\"", __FUNCTION__, command);
	print ("%d arguments:", argc);
	for (int i = 0; i < argc; i++)
		print("     %s", argv[i]);
	return 0;
}

int main( int argc, char** argv )
{
        DEBUG d (__FUNCTION__,__FILE__,__LINE__);
        my_cli*    cli;
        int s, x;
        struct sockaddr_in addr;
	char on = 1;
#ifndef _MSC_VER
	struct termios  OldModes;
#endif

		netInit();

        cli = new my_cli();
        cli->setup();
        cli->set_banner("libcli Video Data Center");
        cli->set_hostname("vdc");

	if (argc > 1)
	{	// read from stdin
		printf("Listening on stdin\n");
		printf("Login with fred/fred, enable with 'fred'\n");
		while (1)
		{
#ifndef _MSC_VER
			( void ) tcgetattr ( fileno (stdin), &OldModes );
#endif
			cli->loop (0);  // stdin
#ifndef _MSC_VER
			( void ) tcsetattr ( fileno ( stdin ), TCSANOW, &OldModes );
#endif
			exit (0);
		}
	}
	// listen to a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(CLITEST_PORT);
	if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		perror("bind");
		return 1;
	}
	if (listen(s, 50) < 0)
	{
		perror("listen");
		return 1;
	}
	printf("Listening on 8000\n");
	printf("Login with x/x, enable with 'x'\n");
	#ifdef WIN32
    HINSTANCE  pTelnet = ShellExecute(NULL, L"open", L"putty.exe", L"-telnet -P 8000 127.0.0.1", NULL, SW_SHOWNORMAL);   
	#endif /* WIN32 */  
        while ((x = accept(s, NULL, 0)))
        {

                cli->loop(x);
				closesocket(x);
        }
        //cli->done();
        return 0;
}
