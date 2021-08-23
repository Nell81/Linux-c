//spwd.c pwd的一个简单版本实现
//bug: 打印根目录“/”，会出现空

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#define BUFFSIZE 15

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char *, int);

int main(){
	printpathto(get_inode("."));	//打印路径
	putchar('\n');					//增加一行
	return 0;
}

void printpathto(ino_t this_inode) {
	ino_t my_inode;
	char its_name[BUFFSIZE];
	if (get_inode("..") != this_inode) {
		if (chdir("..") == -1) perror("chdir");	
		inum_to_name(this_inode, its_name, BUFFSIZE);
		my_inode = get_inode(".");
		printpathto(my_inode);		//递归调用自己
		printf("/%s", its_name);
	}
}

void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen){
	DIR* dir_ptr;
	struct dirent *direntp;
	dir_ptr = opendir(".");
	if (dir_ptr == NULL) {
		perror(".");
		exit(1);
	}
	
	while((direntp = readdir(dir_ptr)) != NULL) {
		if (direntp->d_ino == inode_to_find) {
			strncpy(namebuf, direntp->d_name, buflen);
			namebuf[buflen - 1] = '\0';
			closedir(dir_ptr);
			return;
		}
	}
	fprintf(stderr, "error looking for inum %ld\n", inode_to_find);
	exit(1);
}

ino_t get_inode(char* fname) {
	struct stat info;
	if (stat(fname, &info) == -1) {
		fprintf(stderr, "cannot stat");
		perror(fname);
		exit(1);
	}
	return info.st_ino;
}






