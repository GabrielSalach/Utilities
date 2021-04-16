/* ---------- INCLUDES ---------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------- STRUCTS ---------- */

typedef struct{
    char (***matrix)[32];
    int section_count, value_count;
    char path[64];
}Pe_File;


/* ---------- FUNCTIONS HEADERS ---------- */

Pe_File*            pe_file_create(char *path);                                                 /* Creates a Pe_File struct */
int                 pe_read_file(Pe_File* file);                                                /* Reads the content of the file */
char*               pe_matrix_read(Pe_File* file, int i, int j, int k);                         /* Returns the string in position [i][j][k] in the matrix */
void                pe_file_destroy(Pe_File* file);                                             /* Frees the memory of a Pe_File. */


/* ---------- STRUCT ALLOCATION ---------- */

Pe_File* pe_file_create(char* path) {
    Pe_File* rtrn_file;
    rtrn_file = (Pe_File*) malloc(sizeof (Pe_File));
    strcpy(rtrn_file->path, path);
    return rtrn_file;
}

/* ---------- FILE INPUT ---------- */
/* PENSER A CHECK LE NOMBRE DE SECTIONS CAR SI SECTION = 0 IL FAUT LA REMPLACER PAR DEFAULT DANS LA MATRICE */
int pe_read_file(Pe_File* file) {
    FILE* stream;
    int buffer; /* stored as int so i can know when i reach eof */

    int section_count, value_count;
    section_count = 0;
    value_count = 1;

    stream = fopen(file->path, "r");
    if(file == NULL) {
        printf("The file does not exist.");
        return -1;
    }

    /* Loops through file to count the ammount of sections and values */
    while((buffer = fgetc(stream)) != EOF) {
        if(buffer == ';') {
            while(buffer != '\n' && buffer != EOF) {
                buffer = fgetc(stream);
            }
        } else if(buffer == '[') {
            section_count++;
            while(buffer != '\n' && buffer != EOF) {
                buffer = fgetc(stream);
            }
        } else {
            value_count++;
            while(buffer != '\n' && buffer != EOF) {
                buffer = fgetc(stream);
            }
        }
    }
    file->section_count = section_count;
    file->value_count = value_count;
    printf("Found %d Section and %d value(s)\n", section_count, value_count);
    file->matrix = (char (***)[32]) malloc(sizeof(char*) * section_count * value_count * 2);

    fseek(stream, 0, SEEK_SET);
    /* TODO :
        - Get the right values into the right place ffs
    */

    
}
    
char* pe_matrix_read(Pe_File* file, int i, int j, int k) {
    return file->matrix + (i * file->section_count + j * file->value_count + k);
}

void pe_file_destroy(Pe_File* file) {
    free(file->matrix);
}

