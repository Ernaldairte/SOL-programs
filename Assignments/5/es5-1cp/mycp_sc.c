#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
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
	int fdin = open(argv[1], O_RDONLY);
	if(fdin == -1){
		perror("Opening input file");
		return -1;
	}
	int fdout = open(argv[2], O_WRONLY);
	if(fdout == -1){
		perror("Opening output file");
		return -1;
	}
	int len_rd;
	char buf[copy_size];
	while((len_rd = read(fdin, buf, copy_size)) > 0){
		if(write(fdout, buf, len_rd) != len_rd){
			perror("Writing file");
			return -1;
		}
	}
	if(len_rd == -1){
		perror("Reading file");
		return -1;
	}
	close(fdin);
	close(fdout);
	printf("bescia");
	return 0;
}