/* filesize.c 获得当前目录大小*/

#include <stdio.h>
#include <sys/stat.h>

int main() {
	struct stat infobuf;
	if (stat("/etc/passwd", &infobuf) == -1)
		perror("/etc/passwd");
	else
		fprintf(stdout, "/etc/passwd大小为：%ld\n", infobuf.st_size);
	
	return 0;
}
