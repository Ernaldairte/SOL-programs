extern int optopt;
extern char *optarg;
extern int optind;
extern int opterr;
extern int opreset;

int getopt(int argc, char * const argv[], char * const buf);
int printf(char const *format, ...);


int main(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc,argv, ":n:m:h")) != -1) {
    switch(opt) {
    case 'n':
    case 'm':printf("l'argomento di '-%c' e' '%s'\n",opt, optarg); break;
    case 'h':printf("'-h' non ha argomenti\n"); break;
    case ':':printf("'-%c' richiede un argomento\n", optopt); break;
    case '?':printf("'-%c' non e' riconosciuta\n", optopt);
    default:;
    }
  }  
  return 0;
}
