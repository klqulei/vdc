#ifndef _V_UTILITY_H_
#define _V_UTILITY_H_

#define NOMINMAX
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "tinythread.h"
#include "fast_mutex.h"

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <Ws2tcpip.h>
#include "type.hpp"
#include "libcli.hxx"

using namespace tthread;
using namespace LIBCLI;
using namespace std;

typedef std::string astring;

namespace UtilityLib
{



#ifdef WIN32
inline int socketpair(int    const domain,
                        int    const type,
                        int    const protocol,
                        SOCKET       socks[2]) {
    bool error;

    error = false;  // initial value

    SOCKET listener;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener == INVALID_SOCKET)
        error = true;
    else {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(0x7f000001);
        addr.sin_port = 0;

        int rc;
        rc = bind(listener, (const struct sockaddr*) &addr, sizeof(addr));
        if (rc == SOCKET_ERROR)
            error = true;
        else {
            int addrlen;
            int rc;
            addrlen = sizeof(addr);  // initial value
            rc = getsockname(listener, (struct sockaddr*) &addr, &addrlen);
            if (rc == SOCKET_ERROR)
                error = true;
            else {
                int rc;

                rc = listen(listener, 1);
                if (rc == SOCKET_ERROR)
                    error = true;
                else {
                    socks[0] = socket(AF_INET, SOCK_STREAM, 0);
                    if (socks[0] == INVALID_SOCKET)
                        error = true;
                    else {
                        int rc;
                        rc = connect(socks[0],
                                     (const struct sockaddr*) &addr,
                                     sizeof(addr));
                        if (rc == SOCKET_ERROR)
                            error = true;
                        else {
                            socks[1] = accept(listener, NULL, NULL);
                            if (socks[1] == INVALID_SOCKET)
                                error = true;
                        }
                        if (error)
                            closesocket(socks[0]);
                    }
                }
            }
        }
        closesocket(listener);
    }

    return error ? -1 : 0;
}
#endif

inline unsigned UtilityGetBufferSize(int bufOptName,
                  int socket)
{
  unsigned curSize;
  socklen_t sizeSize = sizeof curSize;
  if (getsockopt(socket, SOL_SOCKET, bufOptName,
         (char*)&curSize, &sizeSize) < 0) {
      //cmn_log(CMN_DEBUG, "getBufferSize() error: ");
    return 0;
  }

  return curSize;
}

inline unsigned UtilityGetSendBufferSize(int socket)
{
  return UtilityGetBufferSize(SO_SNDBUF, socket);
}

inline unsigned UtilityGetReceiveBufferSize(int socket)
{
  return UtilityGetBufferSize(SO_RCVBUF, socket);
}

inline unsigned UtilitySetBufferTo(int bufOptName, int socket, unsigned requestedSize)
{
    int sizeSize = sizeof requestedSize;
    setsockopt(socket, SOL_SOCKET, bufOptName, (char*)&requestedSize, sizeSize);

  // Get and return the actual, resulting buffer size:
  return UtilityGetBufferSize(bufOptName, socket);
}

inline unsigned UtilitySetSendBufferTo(int socket, unsigned requestedSize)
{
    return UtilitySetBufferTo(SO_SNDBUF, socket, requestedSize);
}

inline unsigned UtilitySetReceiveBufferTo(int socket, unsigned requestedSize)
{
    return UtilitySetBufferTo(SO_RCVBUF, socket, requestedSize);
}

inline BOOL makeSocketNonBlocking(int sock) {
#if defined(__WIN32__) || defined(WIN32) || defined(IMN_PIM)
  unsigned long arg = 1;
  return ioctlsocket(sock, FIONBIO, &arg) == 0;
#elif defined(VXWORKS)
  int arg = 1;
  return ioctl(sock, FIONBIO, (int)&arg) == 0;
#else
  int curFlags = fcntl(sock, F_GETFL, 0);
  return fcntl(sock, F_SETFL, curFlags|O_NONBLOCK) >= 0;
#endif
}

template<class T>
class CmdBuffer
{
public:
    CmdBuffer()
    :InFd(-1), OutFd(-1)
    {
        SOCKET fds[2]; /* array of two file descriptors for socketpair */

        s32  nRet = socketpair(AF_INET, SOCK_STREAM, 0, fds);
        if (nRet == -1)
        {

        }
        InFd = fds[0];
        OutFd = fds[1];
        makeSocketNonBlocking((s32)InFd);
        makeSocketNonBlocking((s32)OutFd);

        s32 nRetSize = UtilitySetSendBufferTo(OutFd, 1024 * 1024);


        nRetSize = UtilitySetReceiveBufferTo(InFd, 1024 * 1024);


    }

    ~CmdBuffer()
    {
        closesocket(InFd);
        closesocket(OutFd);
    }

public:
    BOOL Push(T* pMsg)
    {
        if (::send(OutFd, (char *)pMsg, sizeof(T), 0) != sizeof(T))
        {
            return FALSE;
        }

        return TRUE;
    }

    BOOL Pop(T* pMsg)
    {

        if (::recv(InFd, (char *)pMsg, sizeof(T), 0) != sizeof(T))
        {
            return FALSE;
        }


        return TRUE;
    }


public:
    s32 InFd;
    s32 OutFd;
private:
    s32 m_Size;
};

inline void netInit()
{
#ifdef WIN32
	/* Start up the windows networking */
	WORD version_wanted = MAKEWORD(1,1);
	WSADATA wsaData;

	if ( WSAStartup(version_wanted, &wsaData) != 0 ) {
		printf("Couldn't initialize Winsock 1.1\n");
		return;
	}
#endif
}

inline std::string currentDateTime(time_t nTime) 
{
    time_t     now = nTime;
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://www.cplusplus.com/reference/clibrary/ctime/strftime/
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y/%m/%d %X", &tstruct);

    return buf;
}

inline void UtilityDumpTxt(unsigned char *pNuf, int nLen)
{
    int i = 0;
    for (i = 0; i < nLen; i ++)
    {
		printf("%c", pNuf[i]);
    }
	printf("\n\n");
}

inline int image_write_raw (unsigned char *pImg, int size, const char* fname)
{
    FILE * f = NULL;
    int ret;

    f = fopen (fname, "wb");
    if (f == NULL)
    {
        printf ("image_write_raw: fopen failed");
        return -1;
    }

    ret = fwrite(pImg, 1, size, f);
    if (ret != size)
    {
        printf ("image_write_raw: fwrite failed");
        return -1;
    }

    fclose (f);

    return 0;
}

}/* UtilityLib */

#endif /* _VDC_UTILITY_H_ */
