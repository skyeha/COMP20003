#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "read.h"
//#include "data.c"



int main(int argc, char * argv[]) {
    // check for sufficient arguments
    if (argc != 8 || atoi(argv[1]) != 3) {
        printf("Insufficient arguments or incorrect stage number, please try again!\n");
        return EXIT_FAILURE;
    }
    
    // creae outer rectangle space and fill the coordinates
    rectangle2D_t bigRect;
    
    bigRect.botLeft.x = atof(argv[4]);
    bigRect.botLeft.y = atof(argv[5]);

    bigRect.upRight.x = atof(argv[6]);
    bigRect.upRight.y = atof(argv[7]);

    // open dataset
    FILE *data = fopen(argv[2], "r");

    // intialise the root node for quadtree
    quadtreeNode_t *root;
    root = create_node(bigRect);
    assert(root);

    // skip file header
    skip_header(data);
    read_data(data, root);
    
    // start to parse data into quadtree

    fclose(data);
}