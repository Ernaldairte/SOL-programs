#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define CHECK_MEM(p) if(p == NULL){ perror("error:"); exit(EXIT_FAILURE);}
int main(int argc, char *argv[]){
	FILE *passfile = fopen("/etc/master.passwd", "r");
	FILE *resfile = fopen(argv[1], "w");
	char *line = malloc(200 * sizeof(char)); //messo grande apposta perché le skills le verifico sotto
	CHECK_MEM(line);
	size_t dim = 3;
	size_t size = dim;
	char *username = malloc(dim  * sizeof(char)); //messo piccolo apposta per verificare le skills
	CHECK_MEM(username);
	char *charp = NULL;

	while(fgets(line, 200, passfile) != NULL){
		charp = strchr(line, ':');
		if(charp == NULL)
			continue;
		size = abs(charp - line) + 2;
		if(dim < size){
			free(username);
			dim = size;
			username = malloc(dim * sizeof(char));
			CHECK_MEM(username);
		}
		strncpy(username, line, size - 1);
		username[size - 1] = '\0';
		fprintf(resfile, "%s\n", username);

	}
	free(username);
	free(line);

	if(!feof(passfile)){
		if(ferror(passfile)){
			perror("Error in file:");
		}
		else{
			perror("Unkown error:");
		}
	}

}

