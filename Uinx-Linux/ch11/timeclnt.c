/* timeclnt.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>

#define oops(msg) {perror(msg); exit(1);}

int main(int argc, char **argv) {
	struct sockaddr_in servadd;
	struct hostent *hp;
	int sock_id, sock_fd;
	char message[BUFSIZ];
	int messlen;
	
	//第一步，得到一个socket
	sock_id = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_id == -1) {
		oops("socket");
	}
	
	//第二步，连接服务器
	bzero(&servadd, sizeof(servadd));
	
	hp = gethostbyname(argv[1]);
	if (hp == NULL) {
		oops(argv[1]);
	}
	
	bcopy(hp->h_addr, (struct sockaddr*)&servadd.sin_addr, 
			hp->h_length);
	
	servadd.sin_port = htons(atoi(argv[2]));
	
	servadd.sin_family = AF_INET;
	
	if (connect(sock_id, (struct sockaddr*)&servadd, 
		sizeof(servadd)) != 0) {
			oops("connect");
		}
	
	//第三步，传送数据
	messlen = read(sock_id, message, BUFSIZ);
	if (messlen == -1)
		oops("read");
	if (write(1, message, messlen) != messlen) 
		oops("write");
	close(sock_id);
}

























