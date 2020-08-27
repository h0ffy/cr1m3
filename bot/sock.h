#ifndef __SOCK_H_FILE
#define __SOCK_H_FILE


// CC sockets
SOCKET __socket_cc_open();
unsigned long __socket_cc_recv(SOCKET sock, char *buff, int len);
unsigned long __socket_cc_send(SOCKET sock, char *buff);
int __socket_cc_close(SOCKET sock);



#endif