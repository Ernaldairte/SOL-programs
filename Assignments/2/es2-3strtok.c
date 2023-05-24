#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "use: %s stringa1 stringa2\n", argv[0]);
        return -1;
    }
    char *cti, *cto;
    char* token1 = strtok_r(argv[1], " ", &cto);
    char* cparg2 = malloc(strlen(argv[2]));
    if(cparg2 == NULL) exit(-1);
    strcpy(cparg2, argv[2]);

    while (token1) {
        printf("%s\n", token1);
       char* token2 = strtok_r(cparg2, " ", &cti);
       while(token2) {
            printf("%s\n", token2);
            token2 = strtok_r(NULL, " ", &cti);
        }
       strcpy(cparg2, argv[2]);
        token1 = strtok_r(NULL, " ", &cto);
    }
    free(cparg2);
    return 0;
}
