#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PRINT_ERROR(string) fprintf(stderr, string)
#define MAX(a,b) (((a) > (b) ? (a) : (b)))

const int REALLOC_INC=16;
void RIALLOCA(char** buf, size_t newsize) {
    void *tmp = realloc(*buf, newsize);
    if (tmp != NULL)
        *buf = tmp;
    else
        PRINT_ERROR("ran out of memory(probably)");
}
char* mystrcat(char *buf, size_t sz, char *first, ...) {

    if(buf == NULL)
        PRINT_ERROR("buf is null");
    if(first == NULL)
        PRINT_ERROR("first is null");

    va_list ap;
    va_start(ap, first);

    char *next_arg = first;
    char *buf_end = buf;
    size_t source_len;

    do{
        source_len = (size_t) strlen(next_arg);
        if (source_len <= sz)
            strcpy(buf_end, next_arg);
        else{
            RIALLOCA(&buf, MAX(sz + source_len, sz * 2));
            strcpy(buf_end, next_arg);
        }
        next_arg = va_arg(ap, char*);
        buf_end += source_len;

    }
    while(next_arg != NULL);

    return buf;
}

int main(int argc, char *argv[]) {
  if (argc < 7) { printf("troppi pochi argomenti\n"); return -1; }
  char *buffer=NULL;
  RIALLOCA(&buffer, REALLOC_INC);  // macro che effettua l'allocazione del 'buffer'
  buffer[0]='\0'; // mi assicuro che il buffer contenga una stringa
  buffer = mystrcat(buffer, REALLOC_INC, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], NULL);
  printf("%s\n", buffer);
  free(buffer);
  return 0;
}
