#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>


int main(void){
    FILE *fp;
    
    fp = fopen("tmp","r");
    if(fp==NULL){
        fprintf(stderr,"fopen():%s\n",strerror(errno));
        perror("fopen()");
        exit(1);
     }
    
    puts("ok!");
	
    fclose(fp);
    exit(0);
}
