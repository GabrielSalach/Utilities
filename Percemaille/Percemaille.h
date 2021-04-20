/* ---------- INCLUDES ---------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------- STRUCTS ---------- */

typedef struct{
    char*** matrix;
    int section_count, value_count;
    int subsectiont_values[32];
    char path[64];
}Pe_File;


/* ---------- FUNCTIONS HEADERS ---------- */

Pe_File*            pe_file_create(char *path);                                                 /* Creates a Pe_File struct */
int                 pe_read_file(Pe_File* file);                                                /* Reads the content of the file */
void                pe_display_file(Pe_File* file);                                             /* Displays the content of a file */
void                pe_file_destroy(Pe_File* file);                                             /* Frees the memory of a Pe_File */


/* ---------- STRUCT ALLOCATION ---------- */

Pe_File* pe_file_create(char* path) {
    Pe_File* rtrn_file;
    rtrn_file = (Pe_File*) malloc(sizeof (Pe_File));
    strcpy(rtrn_file->path, path);
    return rtrn_file;
}

/* ---------- FILE INPUT ---------- */

int pe_read_file(Pe_File* file) {
    FILE* stream;
    int buffer;
    unsigned int i, j, k;
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
    
    /* COUNTING THE AMOUNT OF SECTIONS AND VALUES */

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
    file->section_count = section_count;
    file->value_count = value_count;
    for(i = 0; i < section_count; i++) {
        file->subsectiont_values[i] = subsection_values[i];
    }
    printf("The program has found %d Sections and %d values.\n", section_count, value_count);
    for(i = 0; i < section_count; i++) {
        printf("    Section %d : %d values\n", i, subsection_values[i]);
    }
    

    /* MEMORY ALLOCATION */
    if(section_count == 0) {
        file->matrix = malloc(sizeof *file->matrix);
        file->matrix[0] = malloc((value_count * 2 + 1) * sizeof *(file->matrix[0]));
        for(i = 0; i < value_count * 2 + 1; i++) {
            file->matrix[0][i] = malloc(32 * sizeof *(file->matrix[0][i]));
        }
    } else {
        file->matrix = malloc(section_count * sizeof *file->matrix);
        for(i = 0; i < section_count; i++) {
            file->matrix[i] = malloc((subsection_values[i] * 2 + 1) * sizeof *file->matrix[i]);
            for(j = 0; j < subsection_values[i] * 2 + 1; j++) {
                file->matrix[i][j] = malloc(32 * sizeof *file->matrix[i][j]);
            }
        }
    }

    /* SETS ALL VALUES TO 0 */
    if(section_count == 0) {
        for(i = 0; i < value_count * 2 + 1; i++) {
            for(j = 0; j < 32; j++) {
                file->matrix[0][i][j] = 0;
            }
        } 
    } else {
        for(i = 0; i < section_count; i++) {
            for(j = 0; j < subsection_values[i] * 2 + 1; j++) {
                for(k = 0; k < 32; k++) {
                    file->matrix[i][j][k] = 0;
                } 
            }
        }
    }
    
    printf("allocation complete\n");

    section_count = 0;
    value_count = 0;
    for(i = 0; i < file->section_count; i++) {
        subsection_values[i] = 0;
    }

    /* READ ALL VALUES */

    fseek(stream, 0, SEEK_SET);

    buffer = fgetc(stream);
    while(buffer != EOF) {
        if(buffer == ';') {
            while(buffer != '\n' && buffer != EOF) {
                buffer = fgetc(stream);
            }
            buffer = fgetc(stream);
        } else if(buffer == '[') {
            buffer = fgetc(stream);
            i = 0;
            while(buffer != ']' && buffer != '\n' && buffer != EOF && i < 32) {
                file->matrix[section_count][0][i] = buffer;
                i++;
                buffer = fgetc(stream);
            }
            buffer = fgetc(stream);                                                                                     /* Skip ']' and '\n' */
            buffer = fgetc(stream);
            while(buffer != '[' && buffer != EOF) {
                if(buffer == ';') {
                    while(buffer != '\n' && buffer != EOF) {
                        buffer = fgetc(stream);
                    }
                    buffer = fgetc(stream);
                } else {
                    i = 0;
                    while(buffer != '=' && buffer != '\n' && buffer != EOF && i < 32) {
                        file->matrix[0][subsection_values[section_count] + 1][i] = buffer;
                        buffer = fgetc(stream);
                        i++;
                    }
                    buffer = fgetc(stream);
                    i = 0;
                    while(buffer != '\n' && buffer != EOF && i < 32) {
                        file->matrix[0][subsection_values[section_count] + 2][i] = buffer;
                        buffer = fgetc(stream);
                        i++;
                    }
                    buffer = fgetc(stream);
                    subsection_values[section_count] += 2;
                }
            }
            section_count++;
        } else {
            i = 0;
            strcpy(file->matrix[0][0], "DEFAULT");
            while(buffer != '=' && buffer != '\n' && buffer != EOF && i < 32) {
                file->matrix[0][value_count+1][i] = buffer;
                buffer = fgetc(stream);
                i++;
            }
            buffer = fgetc(stream);
            i = 0;
            while(buffer != '\n' && buffer != EOF && i < 32) {
                file->matrix[0][value_count+2][i] = buffer;
                buffer = fgetc(stream);
                i++;
            }
            value_count += 2;
            section_count++;
            buffer = fgetc(stream);
        } 
    }
    
    fclose(stream);
    return 0;
}


void pe_file_destroy(Pe_File* file) {
    int i, j;
    if(file->section_count == 0) {
        for(i = 0; i < file->value_count * 2; i++) {
            free(file->matrix[0][i]);
        }
        free(file->matrix[0]);
    } else {
        for(i = 0; i < file->section_count; i++) {
            for(j = 0; j < file->subsectiont_values[i] * 2 + 1; j++) {
                free(file->matrix[i][j]);
            }
            free(file->matrix[i]);
        }
    }
    free(file->matrix);
}

/* ---------- DISPLAY AND READ ---------- */

void pe_display_file(Pe_File* file) {
    if(file->value_count == 0) {
        fprintf(stdout, "The file is empty.\n");
    } else {
        
    }
}