/* twordcount1.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

int total_words;

int main(int argc, char **argv) {
	pthread_t t1, t2;
	void *count_words(void*);
	
	if (argc != 3) {
		fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
		exit(1);
	}	
	total_words = 0;
	pthread_create(&t1, NULL, count_words, (void*)argv[1]);
	pthread_create(&t2, NULL, count_words, (void*)argv[2]);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("%5d: total words\n", total_words);
	
	exit(0);
}

void *count_words(void *f) {
	char *filename = (char*)f;
	FILE *fp;
	int c, prevc = '\0';
	
	if ((fp = fopen(filename, "r")) != NULL) {
		while ((c = fgetc(fp) != EOF)) {
			if (!isalnum(c) && isalnum(prevc))
				total_words++;
			prevc = c;
		}
		fclose(fp);
	} else {
		perror(filename);
	}
	return NULL;
}
