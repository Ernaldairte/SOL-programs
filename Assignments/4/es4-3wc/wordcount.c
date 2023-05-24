#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
void countlines(int *lcount, FILE *inputf);
void countwords(int *wcount, FILE *inputf);
void countwordsandlines(int *wcount, int *lcount, FILE *inputf);

int main(int argc, char *argv[]){
	
	int wcount, lcount;
	char optl = 0, optw = 0, n_opts = 0;
	while(getopt(argc, argv, "wl") != -1){
		if(optopt == 'w')
			optw = 1;
		if(optopt == 'l')
			optl = 1;
	}
	if(argc < 3 || (!optl && !optw)){ 
		printf("usage: %s [-lw] <filename>\n", argv[0]);
		return 0;
	}
	if(optl) n_opts++;
	if(optw) n_opts++;
	int farg = n_opts + 1;
	int f_index = 1;
	while(farg < argc){
		wcount = 0; lcount = 0;
		FILE* inputf = fopen(argv[farg], "r");
		if(inputf == NULL){
			perror("Error");
			return -1;
		}
		printf("File %s - ", argv[farg]);
		if(optw == 1){
			if(optl == 1){
				countwordsandlines(&wcount, &lcount, inputf);
				printf("Line count is: %d and word count is: %d\n", lcount, wcount);
			}else{
				countwords(&wcount, inputf);
				printf("Word count is: %d\n", wcount);
			}
		}else{
			countlines(&lcount, inputf);
			printf("Line count is: %d\n", lcount);
		}
		fclose(inputf);
		farg++;
		f_index++;
	}
	return 0;
}

void countlines(int *lcount,FILE *inputf){
	char *line = malloc(100);
	size_t linecap = 100;
	ssize_t linelen;
	while(getline(&line, &linecap, inputf) != -1){
		(*lcount)++;
	}
}

void countwords(int *wcount, FILE *inputf){
	char *line = malloc(100);
	size_t linecap = 100;
	int i;
	char curchar;
	char reading_word = 0;
	while(getline(&line, &linecap, inputf) != -1){
		i = 0;
		while((curchar = line[i]) != '\0'){
			if(reading_word){
				if(iscntrl(curchar) || isspace(curchar)){
					(*wcount)++;
					reading_word = 0;
				}
			}else{
				if(!iscntrl(curchar) || !isspace(curchar)){
					reading_word = 1;
				}	
			}
			i++;
		}
	}
	if(reading_word){
		(*wcount)++;
	}
}

void countwordsandlines(int *wcount, int *lcount, FILE *inputf){
	char *line = malloc(100);
	size_t linecap = 100;
	int i;
	char curchar;
	char reading_word = 0;
	while( getline(&line, &linecap, inputf) != -1){
		(*lcount)++;
		i = 0;
		while((curchar = line[i]) != '\0'){
			if(reading_word){
				if(iscntrl(curchar) || isspace(curchar)){
					(*wcount)++;
					reading_word = 0;
				}
			}else{
				if(!iscntrl(curchar) && !isspace(curchar)){
					reading_word = 1;	
				}
			}
			i++;
		}
	}
	if(reading_word){
		(*wcount)++;
	}
}

