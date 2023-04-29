#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    int n_found = 0, m_found = 0, o_found = 0;
    int n_arg, m_arg;
    char *o_arg;
    int ch;
    char *endptr = NULL;
    char *result = NULL;
    int cpargc = argc;
    char **cpargv = argv;

    while((ch = getopt(cpargc, cpargv, "n:m:o:h")) != -1){
        switch(ch){
            case 'n':
                if(n_found){
                    fprintf(stderr, "Option -n can't be used more than once");
                    return -1;
                }
                n_found = 1;
                n_arg = (int)strtol(optarg, &endptr, 0);
                if(*endptr != '\0'){
                    fprintf(stderr, "No valid argument for option -n");
                    return -1;
                }
                break;
            case 'm':
                if(m_found){
                    fprintf(stderr, "Option -m can't be used more than once");
                    return -1;
                }
                m_found = 1;
                m_arg = (int)strtol(optarg, &endptr, 0);
                if(*endptr != '\0'){
                    fprintf(stderr, "No valid argument for option -m");
                    return -1;
                }
                break;
            case 'o':
                if(o_found){
                    fprintf(stderr, "Option -o can't be used more than once");
                    return -1;
                }
                o_found = 1;
                o_arg = optarg;
                break;
            case 'h':
                printf("usage: %s -n:int -m:int -o:int", argv[0]);
                return 0;
            default:
                fprintf(stderr, "error");
                return -1;
        }
    }
    printf("Options:");
    if(n_found){
        printf("-n:%d", n_arg);
    }
    if(m_found){
        printf(" -m:%d", m_arg);
    }
    if(o_found){
        printf(" -o:%s", o_arg);
    }
    printf("\n");
}
