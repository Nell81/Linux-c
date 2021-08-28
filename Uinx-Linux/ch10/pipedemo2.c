/* pipedemo2.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHILD_MESS "I want a cookie\n"
#define PAR_MESS "testing..\n"
#define oops(m, x) {perror(m); exit(x);}

int main() {
	int pipefd[2];
	int len;
	char buf[BUFSIZ];
	int read_len;
	
	if (pipe(pipefd) == -1) 
		oops("cannot get a pip", 1);
		
	switch(fork()) {
		case -1:
			oops("cannot fork", 2);
		case 0:
			len = strlen(PAR_MESS);
			while (1) {
				if (write(pipefd[1], PAR_MESS, len) != len)
					oops("write", 4);
				sleep(1);
				read_len = read(pipefd[0], buf, BUFSIZ);
				if (read_len <= 0) 
					break;
				write(1, buf, read_len);
			}
	}
	return 0;
}
