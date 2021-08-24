/* write0.c 发送信息到另一个终端 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 1024

int main(int argc, char** argv) {
	int fd;
	char buf[BUFFSIZE];
	if (argc != 2) {
		fprintf(stderr, "Usage: wirte0 ttyname\n");
		exit(1);
	}
	
	/* open divices */
	fd = open(argv[1], O_WRONLY);
	if (fd == -1) {
		perror(argv[1]);
		exit(1);
	}
	
	/* loop until EOF on input */
	while (fgets(buf, BUFFSIZE, stdin) != NULL) {
		if ((write(fd, buf, strlen(buf)) == -1))
			break;
	}
	
	close(fd);
	return 0;
}
