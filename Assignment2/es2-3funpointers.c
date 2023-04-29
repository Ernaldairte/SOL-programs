#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int h_arg(char *);
int m_arg(char *);
int n_arg(char *);
int o_arg(char *);


int main(int argc, char* argv[]) {
    int (*fun[4]) (char*);
    fun[0] = h_arg;
    fun[1] = m_arg;
    fun[2] = n_arg;
    fun[3] = o_arg;

    int opt;
    while ((opt = getopt(argc,argv, ":n:m:o:h")) != -1) {
        switch(opt) {
            case '?':
                printf("\nOption -%c is not valid", optopt);
             break;
            case ':':
                printf("\nMissing argument for option -%c", optopt);
                break;
            default:
                // invocazione della funzione di gestione passando come parametro l'argomento restituito da getopt
                if (fun[opt%4]( (optarg==NULL ? argv[0] : optarg) ) == -1) {

                }
        }
    }
    return 0;
}

int h_arg(char *arg){
    printf("Usage: %s -n <int> -m <int> -o <string> -h", arg);
    return 0;
}

int n_arg(char *arg){
    char *endptr = NULL;
    int res = (int) strtol(arg, &endptr, 0);
    if(*endptr != '\0' || *arg == '\0') return -1;
    printf("-n:%d ", res);
    return 0;
}

int m_arg(char *arg){
    char *endptr = NULL;
    int res = (int) strtol(arg, &endptr, 0);
    if(*endptr != '\0' || *arg == '\0') return -1;
    printf("-m:%i ", res);
    return 0;
}

int o_arg(char *arg){
    printf("-o:%s ", arg);
    return 0;
}

