#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toint(const char* s) {
   char* e = NULL;
   int val = (int)strtol(s, &e, 0);
   if (s[0] != (char)0 && *e == (char)0) return val; 
   return -1;
}

//Gestisce internamente la stringa dst e la modifica ad ogni chiamata, preoccupandosi di allocarle lo spazio necessario.
//Quando mode vale 0, concatena src a dst.
//Quando mode vale 1, sovrascrive dst con src.
//Restituisce dst
char * alloc_and_write(char *src, char mode){
	static size_t curr_size = 1;
	static size_t space_left = 0;
	static char *dst = NULL;
	static int initialized = 0;
	if(initialized == 0){
		dst = malloc(1);
		dst[0] = '\0';
		initialized = 1;
	}

	size_t src_size = strlen(src);
	
	if(mode == 0){
		if(src_size <= space_left){
			strncat(dst, src, src_size);
			space_left -= src_size;
		}else{
			dst = realloc(dst, ((src_size - space_left) * 2 + curr_size));
			if(dst == NULL){
				fprintf(stderr, "insufficient memory\n");
				exit(1);
			}
			strncat(dst, src, src_size);
			curr_size = (src_size - space_left) * 2 + curr_size;
			space_left = src_size - space_left;
		}
	}
	else{
		if(src_size <= curr_size - 1){
			strcpy(dst, src);
			space_left = curr_size - src_size - 1;
		}else{
			dst = realloc(dst, src_size + 1);
			if(dst == NULL){
				fprintf(stderr, "insufficient memory\n");
				exit(1);
			}
			else{
				strcpy(dst, src);
				curr_size = src_size + 1;
				space_left = 0;
			}
		}
	}
	return dst;
}

char * line_parse(int argc, char **args){	
	int arg_index = 1, curr_char_index = 0;
	char n_found = 0, m_found = 0, s_found = 0;
	char *curr_string = NULL;
	char curr_char;
	char opt_expected = 0;
	char param_expected = 0;
	char param_type = 'i';
	char *result = NULL;
	char *tmp_buf = NULL;

	while(arg_index < argc){
		curr_string = args[arg_index];
		curr_char_index = 0;
		curr_char = curr_string[curr_char_index];
		while(curr_char != '\0' && !param_expected){
			switch(curr_char){
				case '-':
					opt_expected = 1;
					break;

				case 'h':
					if(!opt_expected){
						result = alloc_and_write("wrong formatting, use -h for help\n", 1);
						return result;
					}
					tmp_buf = malloc(sizeof(char) * snprintf(NULL, 0, "usage: %s -n <numero> -m <numero> -s <stringa>\n", args[0]));
					if(tmp_buf == NULL){
						fprintf(stderr, "insufficient memory\n");
						exit(1);
					}
					sprintf(tmp_buf, "usage: %s -n <numero> -m <numero> -s <stringa>\n", args[0]);
					result = alloc_and_write(tmp_buf, 1);
					free(tmp_buf);
					return result;
					
				case 'n':
				case 'm':
				case 's':
					if	(!opt_expected){
						result = alloc_and_write("wrong formatting, use -h for help\n", 1);
						return result;
					}
					if(curr_char == 'n'){
						if(n_found){
							result = alloc_and_write("Same option cannot be given more than once. Use -h for help\n", 1);
							return result;
						}
						n_found = 1;
						param_type = 'i';
					}
					else if(curr_char == 'm'){
						if(m_found){
							result = alloc_and_write("Same option cannot be given more than once. Use -h for help\n", 1);
							return result;
						}
						m_found = 1;
						param_type = 'i';
					}else{
						if(s_found){
							result = alloc_and_write("Same option cannot be given more than once. Use -h for help\n", 1);
							return result;
						}
						s_found = 1;
						param_type = 's';
					}

					tmp_buf = malloc(sizeof(char) * snprintf(NULL, 0, "-%c: ", curr_char));
					if(tmp_buf == NULL){
						fprintf(stderr, "insufficient memory\n");
						exit(1);
					}
					opt_expected = 0;
					param_expected = 1;
					sprintf(tmp_buf, "-%c: ", curr_char);
					alloc_and_write(tmp_buf, 0);
					free(tmp_buf);
					break;

				default: 
					if(!opt_expected){
						result = alloc_and_write("wrong formatting, use -h for help\n", 1);
						return result;
					}
					tmp_buf = malloc(sizeof(char) * snprintf(NULL, 0, "-%c is not a valid option. Use -h for help\n", curr_char));
					if(tmp_buf != NULL){
						sprintf(tmp_buf, "-%c is not a valid option. Use -h for help", curr_char);
						result = alloc_and_write(tmp_buf, 1);
						free(tmp_buf);
						return result;
					}
			}
			curr_char = curr_string[++curr_char_index];
		}

		if(!param_expected){
			result = alloc_and_write("wrong formatting, use -h for help\n", 1);
			return result;
		}

		if(curr_char == '\0'){
			if(++arg_index >= argc){
				result = alloc_and_write("wrong formatting, use -h for help\n", 1);
				return result;
			}
			curr_string = args[arg_index];
			curr_char_index = 0;
			curr_char = curr_string[curr_char_index];
		}

		if(param_type == 'i'){
			int n = toint(curr_string + curr_char_index);
			if(n == -1){
				result = alloc_and_write("wrong formatting, use -h for help\n", 1);
				return result;
			}
			alloc_and_write(curr_string + curr_char_index, 0);
			alloc_and_write(" ", 0);
		}else{
			alloc_and_write(curr_string + curr_char_index, 0);
			alloc_and_write(" ", 0);
		}
		param_expected = 0;
		arg_index++;
	}
	result = alloc_and_write("\n", 0);
	return result;
}


int main (int argc, char *argv[]){

	char *result;
	result = line_parse(argc, argv);
	printf("%s", result);
}
