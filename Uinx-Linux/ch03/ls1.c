/*	ls1.c
**	列出当前目录下的文件和文件夹
**
*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char *);

int main(int argc, char** argv) {
	if (argc == 1) 
		do_ls(".");
	else 
		while (--argc) {
			fprintf(stdout, "%s:\n", * ++argv);
			do_ls(*argv);
		}


	return 0;
}

void do_ls(char dirname[]) {
	DIR* dir_ptr;
	struct dirent *direntp;
	
	if ((dir_ptr = opendir(dirname)) == NULL) 
		fprintf(stderr, "ls1:can not open %s\n", dirname);
	else {
		while ((direntp = readdir(dir_ptr)) != NULL)
			fprintf(stdout, "%s\n", direntp->d_name);
		closedir(dir_ptr);
	}
}











