#include "Percemaille.h"
#include <string.h>
#include <stdio.h>

int main() {
    int read_exit_code;
    Pe_File* file;

    file = pe_file_create("CustomInit.ini");
    read_exit_code = pe_read_file(file);
    printf("Read function returned exit code %d.\n", read_exit_code);
    
    pe_display_file(file);
    pe_file_destroy(file);
    free(file);
   
    return 0;
}