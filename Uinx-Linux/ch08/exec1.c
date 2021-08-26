/* exec1.c 展示如何用一个程序执行另一个程序 */
#include <stdio.h>
#include <unistd.h>

int main() {
	char* arglist[3];
	
	arglist[0] = "ls";
	arglist[1] = "-l";
	arglist[2] = 0;
	printf("*** About to exec ls -l\n");
	execvp("ls", arglist);
	printf("*** ls is done. bye\n");
	return 0;
}
