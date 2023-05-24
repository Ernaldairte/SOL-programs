#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAT_ALLOC(name, rows, columns) malloc(sizeof *name * rows); \
	for(int i = 0; i < columns; i++){\
		name[i] = malloc(sizeof **name * columns);}\

int matcmp(int (*fcmp)(const void*, const void* , size_t s), char *filename1, char *filename2, 
		   size_t size, char *program_name);


int main(int argc, char *argv[]){
	if(argc < 2){
		printf("usage: %s <size>\n", argv[0]);
		return -1;
	}
	size_t size = (size_t) strtol(argv[1], NULL, 0);
	FILE *mat_b = fopen("mat_dump.dat", "w");
	FILE *mat_t = fopen("mat_dump.txt", "w");
	if(mat_b == NULL || mat_t == NULL){
		perror("Error");
		return -1;
	}
	float elem;
	int i, j;
	for(i = 0; i < size; i++){
		for(j=0; j<size; j++){
			elem = (i+j)/2.0;
			fprintf(mat_t, "%f\n", elem);
			fwrite(&elem, sizeof(float), 1, mat_b);
		}
	}
	fclose(mat_t);
	fclose(mat_b);
	int res = matcmp(memcmp, "mat_dump.txt", "mat_dump.dat", size, argv[0]);
	printf("Risultato: %d\n", res);
}

int matcmp(int (*fcmp)(const void*, const void*, size_t), char *filename1, char *filename2, 
		   size_t size, char *program_name){
	char *res = NULL;
	
	if((res = strstr(filename1, ".txt")) == NULL || (res = strstr(filename2, ".dat")) == NULL) 
		return -1;
	if(strlen(res) != 4) 
		return -1;

	FILE *mat_t = fopen(filename1, "r");
	FILE *mat_b = fopen(filename2, "r");
	float **M1 = MAT_ALLOC(M1, size, size);
	float **M2 = MAT_ALLOC(M2, size, size);
	float *m2buf = malloc(sizeof(float) * 100);
	fread(m2buf, sizeof(float), 100, mat_b);

	char *line = malloc(100);
	size_t linecap = 100;
	ssize_t linelen;
	char *end; 
	float val;

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			linelen = getline(&line, &linecap, mat_t);
			if(linelen < 1)
				break;
			line[linelen - 1] = '\0';
			val = strtof(line, &end);
			if(!(*line != '\0' && *end == '\0')){
				fprintf(stderr, "File contains data which is not a number\n");
				return -1;
			}
			M1[i][j] = val;
			M2[i][j] = *(m2buf + (size * i) + j);
		}
	}
	fclose(mat_t);
	fclose(mat_b);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(fcmp(&M1[i][j], &M2[i][j], sizeof(float)) != 0)
				return -1;

		}
	}

	/*FILE *fp = fopen("test.txt", "w");
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			fprintf(fp, "%f\n", M2[i][j]);
		}
	}*/
	return 0;
}

