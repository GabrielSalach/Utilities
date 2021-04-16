/* ---------- INCLUDES ---------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------- STRUCTS ---------- */

typedef struct{
    char**** matrix;
    char path[64];
}Pe_File;


/* ---------- FUNCTIONS HEADERS ---------- */

Pe_File             *pe_file_create(char *path);                                                    /* Creates a Pe_File struct */

int                pe_read_file(char* path);                                                       /* Reads the content of the file */


/* ---------- STRUCT ALLOCATION ---------- */

Pe_File *pe_file_create(char *path) {
    Pe_File* rtrn_file;
    strcpy(rtrn_file->path, path);
}

/* ---------- FILE INPUT ---------- */

int pe_read_file(char* path) {
    FILE* file;
    char rtrn_string[128];
    char buffer[1];

    file = fopen(path, "r");
    if(file == NULL) {
        printf("The file does not exist.");
        return -1;
    }
    fscanf(file, "%c", buffer);
    printf("%s;\n", buffer);
    printf("%d\n", memcmp("a", buffer, 2));
    
    return 0;
}

