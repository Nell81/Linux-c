#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include<mcheck.h>

// void cleanup(char** pointer) {
//   free(*pointer);
//   *pointer = NULL;
// }

// 自行实现getline函数
ssize_t mygetline(char** line, size_t *n, FILE *fp)
{
    char *buf = *line;
    //c来存储字符，i来记录字符串长度
    ssize_t c =0;
    ssize_t i =0;

    //buf为空或n为0时动态分配空间
    if(buf == NULL || *n==0)
    {
        *line = malloc(10);
        buf = *line;
        *n = 10;
    }

    while((c = fgetc(fp)) != '\n')
    {
        if(c == EOF)
            return -1;
        //留2个空间给'\n'和'\0'
        if(i < *n - 2)
            *(buf + i++) = c;
        else
        {
            //空间不足,需要扩展空间，重新进行分配
            *n = *n + 10;
            buf = realloc(buf, *n);
            *(buf + i++) = c;
        }
    }

    *(buf + i++)='\n';
    *(buf + i)='\0';
    return i;
}

int main(int argc, char **argv)
{
    
    // mtrace();
    FILE *fp;
    char *linebuf = NULL;
    size_t linesize = 0;

    if(argc < 2)
    {   
        fprintf(stderr, "Usage:%s <src_file>\n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    
    while(1)
    {
        if(mygetline(&linebuf, &linesize, fp) < 0) // if(getline(&linebuf, &linesize, fp) < 0)
            break;
            printf("%lu\n", strlen(linebuf));
            printf("%lu\n", linesize);
    }

    fclose(fp);
    free(linebuf);
    exit(0);
}