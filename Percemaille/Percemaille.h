/* ---------- INCLUDES ---------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------- STRUCTS ---------- */

typedef struct{
    char (**matrix)[32];
    int section_count, value_count;
    int subsectiont_values[32];
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
    int buffer;
    unsigned int i;
    int section_count, value_count;
    int subsection_values[32];
    section_count = 0;
    value_count = 0;

    /* NEED TO CHECK IF THE FILE IS A .INI */

    for(i = 0; i < 32; i++) {                                                                                   /* Initializes the subsection_values array to 0. */
        subsection_values[i] = 0;
    }

    stream = fopen(file->path, "r");
    if(file == NULL) {
        printf("The file does not exist.");
        return -1;
    }
    buffer = fgetc(stream);
    
    while(buffer != EOF) {                                                                                      /* Loops through file to count the ammount of sections and values */
        if(buffer == ';') {                                                                                     /* Ignores comment */
            while(buffer != '\n' && buffer != EOF) {
                buffer = fgetc(stream);
            }
            buffer = fgetc(stream);                                                                             /* Sets the buffer to the next value after \n for the next check */
        } else if(buffer == '[') {                                                                              /* Adds 1 section and read until the end of line*/
            section_count++;
            while(buffer != '\n' && buffer != EOF) {
                buffer = fgetc(stream);
            }
            buffer = fgetc(stream);                                                                             /* Sets the buffer to the next value after \n for the next check */
            while(buffer != '[' && buffer != EOF) {                                                             /* Count every value under this section until it reaches another region or a comment */
                if(buffer != ';') {                                                                             /* Adds value to the subsection count */
                    value_count++;
                    subsection_values[section_count - 1] += 1;
                    while(buffer != '\n' && buffer != EOF) {
                        buffer = fgetc(stream);
                    }
                } else {                                                                                        /* Ignores line if its a comment */
                    while(buffer != '\n' && buffer != EOF) {
                        buffer = fgetc(stream);
                    }
                }
                buffer = fgetc(stream);                                                                         /* Sets the buffer to the next value after \n for the next check */
            }
        } else {                                                                                                /* Value without section first */
            value_count++;
            while(buffer != '\n' && buffer != EOF) {
                buffer = fgetc(stream);
            }
            buffer = fgetc(stream);                                                                             /* Sets the buffer to the next value after \n for the next check */
        }
    }
    
    printf("The program has found %d Sections and %d values.\n", section_count, value_count);
    for(i = 0; i < section_count; i++) {
        printf("    Section %d : %d values\n", i, subsection_values[i]);
    }
    

    file->section_count = section_count;
    file->value_count = value_count;
    if(section_count == 0) {                                                                                    /* If there are no sections at all in the file */
        file->matrix = (char (**)[32]) malloc(sizeof (char**));
        file->matrix[0] = (char (*)[32]) malloc(sizeof(char*) * value_count * 2);
        printf("allocated %d bytes to matrix[0]\n", (int) (sizeof (char*) * value_count * 2));
    } else {                                                                                                    /* Else, allocates the right number of subvalues to each section */
        file->matrix = (char (**)[32]) malloc(sizeof (char**) * section_count);
        for(i = 0; i < section_count; i++) {
            file->matrix[i] = (char (*)[32]) malloc(sizeof (char*) * subsection_values[i] * 2);
            printf("allocated %d bytes to matrix[%d]\n", (int) (sizeof (char*) * subsection_values[i] * 2), i);
        }
    }
    
    

    fseek(stream, 0, SEEK_SET);                                                                                 /* Returns to the beginning of the file. */



    
    return 0;

    
}
    
/* char* pe_matrix_read(Pe_File* file, int i, int j, int k) {
    return NULL;
} */

void pe_file_destroy(Pe_File* file) {
    int i;
    if(file->section_count == 0) {
        free(file->matrix[0]);
    } else {
        for(i = 0; i < file->section_count; i++) {
            free(file->matrix[i]);
        }
    }
    free(file->matrix);
}

