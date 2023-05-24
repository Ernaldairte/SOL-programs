#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define PRINT_USAGE printf("usage: %s filein fileout [buffersize]\n", argv[0]);

int main(int argc, char *argv[]){
	if(argc < 3 || argc > 4){
		PRINT_USAGE;
		return -1;
	}
	int copy_size = 1;
	char *end;
	if(argc == 4){
		copy_size = (int)strtol(argv[3], &end, 0);
		if(*argv[3] == '\0' || *end != '\0'){
			PRINT_USAGE;
		return -1;
		}
	}
	FILE *fdin = fopen(argv[1], "r");
	if(fdin == NULL){
		perror("Opening input file");
		return -1;
	}
	FILE *fdout = fopen(argv[2], "w");
	if(fdout == NULL){
		perror("Opening output file");
		return -1;
	}
	char buf[copy_size];
	int len_rd;
	while((len_rd = fread(buf, 1, copy_size, fdin))  != 0){
		if(fwrite(buf, 1, len_rd, fdout) != len_rd){
			perror("Writing file");
			return -1;
		}
	}
	if(!feof(fdin)){
		perror("Reading file");
		return -1;
	}

	fclose(fdin);
	fclose(fdout);
	return 0;
}