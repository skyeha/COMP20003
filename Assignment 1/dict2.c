#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dict2_ops.h"
#include "general.h"

int main(int argc, char *argv[]) {
    //check arguments
    check_args(argc, argv);

    // create dynamic array and linked list
    array_t *array;
    dictionary_t *dict;
    dict = make_dict();
    array = build_array();
    assert(array && dict);

    // Open dataset file and check if successful
    FILE *file_in;
    file_in = fopen(argv[2], "r");

    if (!file_in) {
        printf("Failed to read file! Please try again\n");
        exit(EXIT_FAILURE);
    }

    //skip header line of file_in and parse data into linked list and array
    skip_header(file_in);
    read_data(array, dict, file_in);
    fclose(file_in);

    // removing all excessive memory
    reduce_size(array);

    //sort the array;
    do_quicksort(array);

    // create file for output;
    FILE *file_out = fopen(argv[3], "w");
    char buffer[MAX_FIELD_SIZE + 1];
    while (fgets(buffer, MAX_FIELD_SIZE, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        record_search(array, buffer, file_out);
    }

    fclose(file_out);
    free_array(array, dict);
    
}