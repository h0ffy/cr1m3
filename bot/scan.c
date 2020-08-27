#include <windows.h>
#include <winsock2.h>
#include <mswsock.h>
#include "scan.h"


/*
 * @brief Scan 1 tcp port using connect technique
 * @param host string with host or ip 
 * @param port ?? wh0?? wh0??
 * @returns 0 close
 *          1 open r0x!!
 */
int __scan_port_tcp_connect(char *host, unsigned int port) {
        WSADATA wsa = {0};
        SOCKET sock = 0xFFFFFFFF;
        SOCKADDR_IN addr_out = {0};
        struct hostent *shost;

        WSAStartup(MAKEWORD(2,2),&wsa);


        if(!(shost = gethostbyname(host))) {
		if(!(inet_addr(host))
                	return 0;
		else
			addr_out.sin_addr.s_addr = inet_addr(host);

	}
	else {
		addr_out.sin_addr =  *((struct in_addr *)shost->h_addr); //  mov [eax+sin_addr], [shost].h_addr
	}

        addr_out.sin_family = AF_INET;
        addr_out.sin_port = htons(port);
        ZeroMemory(addr_out.sin_zero,8);


        if((sock=WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0))==(~0)) {
                return 0;
        }

        if(WSAConnect(sock, (SOCKADDR *)&addr_out, sizeof(addr_out), 0 , 0, 0, 0)==SOCKET_ERROR) {
                        if(sock)
                                closesocket(sock);

                        return 0;
        }
		
	closesocket(sock);
	WSACleanup();
	return 1;
}

