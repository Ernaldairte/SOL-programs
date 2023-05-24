#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "use: %s stringa1 stringa2\n", argv[0]);
        return -1;
    }
        int flag1 = tokenizer(argv[1], argv[2]);
        if(flag1 == -1)
            printf("usage: %s arg1 arg2", argv[0]);
        else
            tokenizer_r(argv[1], argv[2]);

    return 0;
}
