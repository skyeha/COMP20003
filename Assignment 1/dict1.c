#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "general.c"
#include "dict1_ops.h"


int main(int argc, char *argv[]) {
    //check for correct arguments

    check_args(argc, argv);
    
    // Create the dictionary
    dictionary_t *dict;
    dict = make_dict();

    // Open the file in the directory and check if open successfully
    FILE *file_in;
    file_in = fopen(argv[2], "r");

    if (file_in == NULL){
        printf("Failed to read file!\n");
        exit(EXIT_FAILURE);
    }

    // parse data and close file after finished
    skip_header(file_in);
    read_data(dict, file_in, NULL);
    fclose(file_in);

    // writing answer into output.txt and result in stdout
    FILE *file_out;
    file_out = fopen(argv[3], "w");
    char buffer[MAX_ROW_SIZE + 1];
    while (fgets(buffer, MAX_FIELD_SIZE + 1, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        address_lookup(dict, buffer, file_out);
    }
    
    // close output file after finishing writing
    fclose(file_out);

    // free all the allocated memory
    free_dict(dict);

    return 0;
}


