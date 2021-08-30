/* timeserv.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>

#define PORTNUM 13000
#define HOSTLEN 256
#define oops(m) {perror(m); exit(1);}

int main(int argc, char **argv) {
	struct sockaddr_in saddr;
	struct hostent *hp;
	char hostname[HOSTLEN];
	int sock_id, sock_fd;
	FILE *sock_fp;
	char *ctime();
	time_t thetime;
	
	//第一步，请求一个socket
	sock_id = socket(PF_INET, SOCK_STREAM, 0);
	if (sock_id == -1) {
		oops("sock");
	}
	
	//第二步，绑定地址到socket上
	
	bzero((void*) &saddr, sizeof(saddr));
	gethostname(hostname, HOSTLEN);
	hp = gethostbyname(hostname);
	
	bcopy((void*)hp->h_addr, (void*)&saddr.sin_addr, 
			hp->h_length);
	saddr.sin_port = htons(PORTNUM);
	saddr.sin_family = AF_INET;
	
	if (bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0) {
		oops("bind");
	}
	
	//第三步，在socket上，允许接入呼叫并设置队列长度为1
	if (listen(sock_id, 1) != 0) {
		oops("listen");
	}
	
	/* main loop:accept(), write(), close() */
	
	while (1) {
		sock_fd = accept(sock_id, NULL, NULL);
		printf("Wow! got a call!\n");
		if (sock_fd == -1) {
			oops("accept");
		}
		sock_fp = fdopen(sock_fd, "w");
		if (sock_fp == NULL) {
			oops("fdopen");
		}
		thetime = time(NULL);
		
		fprintf(sock_fp, "The time her is ...");
		fprintf(sock_fp, "%s", ctime(&thetime));
		fclose(sock_fp);
	}
}
