/* forkdemo2.c 展示子进程返回的起始位置 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("my pid is %d\n", getpid());
	fork();
	fork();
	fork();
	printf("my pid is %d\n", getpid());
}
