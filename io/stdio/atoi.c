#include<stdio.h>
#include<stdlib.h>




int main(void){

    char str[] = "123456";
    printf("%d\n",atoi(str));

    char buf[1024];
    int year = 2020, month = 12, day = 30;
    sprintf(buf, "%d-%d-%d", year, month, day);
    puts(buf);
    
    exit(0);
}
 
