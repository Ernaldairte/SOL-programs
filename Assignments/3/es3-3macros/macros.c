#include <stdlib.h>
#include <stdio.h>

#define dimN 16
#define dimM  8

#define CHECK_PTR_EXIT(ptr, msg) \
            if(ptr == NULL){ perror(msg); \
                exit(EXIT_FAILURE);}
#define ELEM(M, arg1, arg2) *(M + dimM * arg1 + arg2)

#define PRINTMAT(M, rows, columns) \
            for(size_t l = 0; l < rows; l++){ \
                for(size_t m = 0; m < columns; m++){ \
                    printf("%ld\n", ELEM(M,l, m)); \
            }\
        }

        
        

int main() {
    
    long *M = malloc(dimN*dimM*sizeof(long));

    CHECK_PTR_EXIT(M, "malloc"); 
    for(size_t i=0;i<dimN;++i)
    for(size_t j=0;j<dimM;++j){			
	    ELEM(M,i,j) = i+j;    
    }
        PRINTMAT(M, dimN, dimM);
    free(M);
    return 0;
}