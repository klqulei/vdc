#ifndef _V_DEBUG_H_
#define _V_DEBUG_H_

#include "utility.hpp"
#define NOMINMAX

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#include "shellapi.h"
#endif

namespace UtilityLib
{
	
class Debug : public CLI
{
public:
	static void run(void * pParam)
	{
		if (pParam)
		{
			Debug * pDebug = (Debug *)pParam;
			pDebug->run1();
		}
	}
	void run1()
	{
	    int s, x;
        struct sockaddr_in addr;
		char on = 1;
		
		// listen to a socket
		if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("socket");
			return ;
		}
		setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(9000);
		if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
		{
			perror("bind");
			return ;
		}
		if (listen(s, 50) < 0)
		{
			perror("listen");
			return ;
		}
		printf("Listening on 9000\n");
		printf("Login with x/x, enable with 'x'\n");
#ifdef WIN32
		HINSTANCE  pTelnet = ShellExecute(NULL, L"open", L"putty.exe", L"-telnet -P 9000 127.0.0.1", NULL, SW_SHOWNORMAL);   
#endif /* WIN32 */  
        while ((x = accept(s, NULL, 0)))
        {

			this->loop(x);
			closesocket(x);
        }

        return ;	
	}

public:
	static void init(s32 nPort)
	{
		if (gDebug != NULL)
		{
			return;
		}
		netInit();
		gDebug = new Debug();
        gDebug->setup();
        gDebug->set_banner("V");
        gDebug->set_hostname("V");
		
		gThread = new thread(Debug::run, (void *)gDebug);
		
		return;
		
	}
	static void DebugPrint( const char* format, ... )
	{
		va_list vl;
		va_start(vl, format);
		gDebug->bufprint(currentDateTime(time(NULL)).c_str());
		gDebug->bufprint(" [V]: ");
		gDebug->vabufprint(format, vl);
		va_end(vl);
	}
	

	
public:
	void setup()
	{
		typedef Command<CLI>::cpp_callback_func callback_ptr;
		typedef CLI::cpp_auth_func auth_callback;
		typedef CLI::cpp_enable_func enable_callback;
		Command<CLI>* c;
		Command<CLI>* c2;

		set_auth_callback( static_cast<auth_callback> (& Debug::check_auth) );
		set_enable_callback( static_cast<enable_callback> (& Debug::check_enable) );
		
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
			static_cast<callback_ptr> (&Debug::test),
			LIBCLI::UNPRIVILEGED,
			LIBCLI::MODE_ANY,
			"Show version information"
		), c);

		c2 = new Command<CLI> (
			this,
			"blacklist",
			static_cast<callback_ptr> (&Debug::test),
			LIBCLI::UNPRIVILEGED,
			LIBCLI::MODE_ANY,
			"Show list"
		);
		register_command (c2, c);

		register_command ( new Command<CLI> (
			this,
			"brief",
			static_cast<callback_ptr> (&Debug::test),
			LIBCLI::UNPRIVILEGED,
			LIBCLI::MODE_ANY,
			"Show list brief"
		), c2);
	}
	
	int  check_auth (const string& username, const string& password)
	{
		if (username != "x")
			return -1;
		if (password != "x")
			return -1;
		return LIBCLI::OK;
	}
	int  check_enable(const string& password)
	{
		return (password == "x");
	}
	
	

public:
	int test (char *command, char *argv[], int argc)
	{
		print("V Hello %d\n", 1);
		return 0;
	}
	
private:
	static Debug * gDebug;
	static thread *gThread;

};

}

#define  VDC_DEBUG UtilityLib::Debug::DebugPrint

#endif /* _VDC_UTILITY_H_ */
