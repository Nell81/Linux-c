#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>


int main(void){
    FILE *fp;
    int count = 0;

    while(1)
    {    
        fp = fopen("tmp","r");
        if(fp==NULL){
            perror("fopen()");
            break;
        }
        count++;
    }
    
    printf("count = %d\n",count);
	
    // fclose(fp);
    exit(0);
}
