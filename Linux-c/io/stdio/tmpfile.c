#include <stdio.h>
#include <stdlib.h>

//tmpfile函数创建并打开一个临时文件（二进制，在 /tmp文件夹中），并且自动执行了unlink。
//tmpfile函数返回一个文件描述符，如果执行失败返回NULL。当程序执行了fclose或者退出时，资源被释放。

int main()
{
    FILE *tempfp;
    char line[256];
    char buf[256];
    //创建临时文件
    tempfp=tmpfile();
    if(tempfp==NULL)
    {
        perror("tmpfile()");
        return -1;
    }

    printf("Opened a temporary file OK!\n");
    //把数据写到临时文件流中
    fputs("One line of output \n",tempfp);
    //重置流到文件头
    rewind(tempfp);
     //从临时文件流中读取数据
    if(fgets(line, sizeof(line),tempfp) == NULL)
    {
        perror("fgets()");
        return -2;
    }
    //标准输出
    fputs(line, stdout);
   //再次读取需要重置流到文件头
    rewind(tempfp);
    //tmpfile创建的临时文件只能读取一次，读取之后里面的内容就没有了
    fgets(buf,sizeof(buf),tempfp);
    fputs(buf, stdout);


    exit(0);
}