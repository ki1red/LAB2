#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isNumber(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i])){
            return 0;
        }
    }

    return 1;
}


int main(int argc, char* argv[]){

    if (argc != 5) {
        printf("Usage: %s <func-name> <old-file> <new-file> <symbol> \n", argv[0]);
        exit(-1);
    }

    if(!isNumber(argv[2])){
        printf("Wrong numbers value argument: %s\n", argv[2]);
        exit(-4);
    }

    char* dot_vol = argv[2];
    int value = atoi(dot_vol);

    if (value<0){
        printf("Wrong numbers value argument: %s\n", argv[2]);
        exit(-4);
    }

    void *ext_library;

    int (*powerfunc)(int value, const char *filename1, const char *filename2);

    ext_library = dlopen("/home/dyb/CLionProjects/libpowers.so",RTLD_LAZY);
    if (!ext_library){

        fprintf(stderr,"dlopen() error: %s\n", dlerror());
        return 1;
    };

    printf("Library loaded!\n");

    powerfunc = dlsym(ext_library, argv[1]);

    printf(argv[1],((*powerfunc)(value, argv[3], argv[4])));
    dlclose(ext_library);
};