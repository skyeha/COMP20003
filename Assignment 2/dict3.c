#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "read.h"

int main(int argc, char * argv[]) {
    // check for sufficient arguments
    if (argc != 8 || atoi(argv[1]) != 3) {
        printf("Insufficient arguments or incorrect stage number, please try again!\n");
        return EXIT_FAILURE;
    }
    
    // creae outer rectangle space and fill the coordinates
    rectangle2D_t bigRect;
    char value[sizeof(long double) + 1];
    char *eptr;
    strcpy(value, argv[4]);
    bigRect.botLeft.x = strtold(value, &eptr);

    strcpy(value, argv[5]);
    bigRect.botLeft.y = strtold(value, &eptr);
    
    strcpy(value, argv[6]);
    bigRect.upRight.x = strtold(value, &eptr);

    strcpy(value, argv[7]);
    bigRect.upRight.y = strtold(value, &eptr);

    // open dataset
    FILE *fileIn = fopen(argv[2], "r");
    assert(fileIn);

    // intialise the root node for quadtree
    quadtreeNode_t *root;
    
    root = createNode(&bigRect);
    assert(root);

    // skip file header
    skipHeader(fileIn);
    readData(fileIn, root);
    
    coordinates_t query;
    FILE *fileOut = fopen(argv[3], "w");
    char buffer[MAX_ROW_SIZE + 1];
    char *token,
          *record;
    while (fgets(buffer, MAX_FIELD_SIZE + 1, stdin) != NULL) {
        buffer[strcspn(buffer,"\n")] = '\0';
        record = strdup(buffer);
        char *dup_str_addr = record;
        while ((token = strsep(&record, " ")) != NULL) {
            query.x = atof(token);
            token = strsep(&record, " ");
            query.y = atof(token);
        }
        searchPoint(&query, buffer, root, 0, fileOut);
        free(dup_str_addr);
    }
    
    freeTree(root);
    fclose(fileIn);
    fclose(fileOut);
}