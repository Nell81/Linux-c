/* sigdemo2,c 显示如何忽略信号 
  2  * ctrl-\ 可以杀死该进程
  3  * */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
	signal(SIGINT, SIG_IGN);
	printf("you cannot stop me!\n");
	while (1) {
	 sleep(1);
	 printf("haha\n");
	}                                                             
}

