/* forkdemo3.c 进程根据fork返回值不同打印不同的消息 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int fork_rv;
	
	printf("Before: my pid is %d\n", getpid());
	
	fork_rv = fork();
	
	if (fork_rv == -1) 
		perror("fork");
	else if (fork_rv == 0)
		printf("I am a child. my pid is %d\n", getpid());
	else 
		printf("I am a parent. my pid is %d\n", getpid());
}
