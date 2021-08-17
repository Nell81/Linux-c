#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void tempFile()
{
    int fd = 0;
    char filename[] = "/tmp/temp_XXXXXX";

    char buf1[50] = "Hello tempfile.";
    char buf2[50];
    int len = 0;

    if((fd = mkstemp(filename)) < 0)
    {
        perror("mkstemp()");
        return ;
    }
    printf("Template file name:%s\n", filename);
    len = write(fd, buf1, strlen(buf1)); //写数据到临时文件中
    lseek(fd,0,SEEK_SET);  //重新把文件指针偏移到文件头
    read(fd, buf2, len);  //从临时文件中读出数据

    printf("%s\n", buf2);
 
    close(fd);
    //程序结束后系统会自动删除临时文件
    unlink(filename);
}


int main() {
    tempFile();
    exit(0);
}