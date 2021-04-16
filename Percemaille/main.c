#include "Percemaille.h"
#include <string.h>
#include <stdio.h>

int main() {
    /* char* matrix[2][2][2];
    int i, j;
    matrix[0][0][0] = "Cat1";
    matrix[0][1][0] = "Val1";
    matrix[0][1][1] = "valeur";
    matrix[1][0][0] = "cat2";
    matrix[1][1][0] = "val2";
    matrix[1][1][1] = "valeur";
    for(i = 0; i < 2; i++) {
        if(strcmp(matrix[i][0][0], "Cat1") == 0) {
            printf("found Cat 1 at %d\n", i);
            for(j = 0; j < 2; j++) {
                if(strcmp(matrix[i][j][0], "Val1") == 0) {
                    printf("found val1 at %d %d\n", i, j);
                    printf("[Cat1] val1 = %s - [%d][%d][%d]\n", matrix[i][j][j], i, j, j);
                }
            }
        }
        
    } */

    Pe_File* file;
    file = pe_file_create("test.txt");
    if(pe_read_file(file) == 0){
        printf("0\n");
    }
    pe_file_destroy(file);
    free(file);
    return 0;
}