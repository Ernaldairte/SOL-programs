#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int tokenizer_r(char* string1, char* string2){
  
    char *cti, *cto;
    char *cparg1 = malloc(strlen(string1));
    char *cparg2 = malloc(strlen(string2));
    printf("Tokenizer_r:\n");
    if(cparg1 == NULL || cparg2 == NULL) return -1;
    strcpy(cparg1, string1);
    strcpy(cparg2, string2);
    char *token1 = strtok_r(cparg1, " ", &cto);

    while (token1) {
        printf("%s\n", token1);
       char* token2 = strtok_r(cparg2, " ", &cti);
       while(token2) {
            printf("%s\n", token2);
            token2 = strtok_r(NULL, " ", &cti);
        }
       strcpy(cparg2, string2);
        token1 = strtok_r(NULL, " ", &cto);
    }
    printf("\n");
    free(cparg1);
    free(cparg2);
    return 0;
}
