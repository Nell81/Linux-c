#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST

void show_info(struct utmp * utbufp);
void showtime(long timeval);

int main(){
	struct utmp current_record;
	int 		utmpfd;
	int 		reclen = sizeof(current_record);
	
	if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
		perror(UTMP_FILE);
		exit(1);
	}
	
	while (read(utmpfd, &current_record, reclen) == reclen) {
		show_info(&current_record);
	}
	close(utmpfd);
	return 0;
}

void show_info(struct utmp * utbufp) {
	if (utbufp->ut_type != USER_PROCESS) 
		return;
	printf("%-8.8s", utbufp->ut_name);
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);
	printf(" ");
	showtime(utbufp->ut_time);
	if (utbufp->ut_host[0] != '\0')
		printf("(%s)", utbufp->ut_host);
	printf("\n");
}

void showtime(long timeval) {
	char* cp;
	cp = ctime(&timeval);
	printf("%12.12s", cp + 4);
}



