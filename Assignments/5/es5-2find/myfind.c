#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
int myfind();
#define PRINT_USAGE printf("usage: %s directory file", argv[0])

char *name = NULL;

int main(int argc, char *argv[]){
	if(argc != 3){
		PRINT_USAGE;
		return -1;
	}
	name = malloc(strlen(argv[2]) + 1);
	if(name == NULL){
		perror("Allocating buffer");
		return -1;
	}

	name = argv[2];
	chdir(argv[1]);
	myfind();
}
	
int myfind(){
	DIR *curr_dir = opendir(".");
	if(curr_dir == NULL){
		perror("Opening directory");
		return -1;
	}
	struct dirent *next_entry;
	struct stat info;
	char *entry_name;
	char *path;
	while((errno = 0, next_entry = readdir(curr_dir)) != NULL){
		entry_name = next_entry->d_name;
		if(strcmp(entry_name,".") == 0 || strcmp(entry_name,"..") == 0)
			continue;
		if(stat(entry_name, &info) == -1){
			perror("Retrieving file info");
			return -1;
		}
		if(strncmp(name, entry_name, 255) == 0){
			path = realpath(entry_name, NULL);
			if(path == NULL){
				perror("While getting path");
				return -1;
			}
			printf("path:%s\nlast modified:%s", path, ctime(&(info.st_mtime)));
			free(path);
		}
		if(S_ISDIR(info.st_mode)){ 
			char *prev_path = getwd(NULL);
			chdir(entry_name);
			myfind();
			chdir(prev_path);
			free(prev_path);
		}

	}
	if(errno != 0){
		perror("Navigating directories");
		return -1;
	}
	closedir(curr_dir);
	return 0;
}