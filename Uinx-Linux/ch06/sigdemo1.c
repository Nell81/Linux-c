/* sigdemo1.c 显示信号如何捕捉的 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
	void f(int);
	int i;
	signal(SIGINT, f);
	for (int i = 0; i < 5; i++) {
		printf("hello\n");
		sleep(1);
	}
	return 0;
}

void f(int signum) {
	printf("OUCH!\n");
}
