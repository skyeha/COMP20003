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
    rectangle2D_t rect;
    
    rect.bot_left.lon = atof(argv[4]);
    rect.bot_left.lat = atof(argv[5]);

    rect.up_right.lon = atof(argv[6]);
    rect.up_right.lat = atof(argv[7]);

    // open dataset
    FILE *data = fopen(argv[2], "r");

    // intialise the root node for quadtree
    quadtreeNode_t *root_node;
    root_node = create_node();
    assert(root_node);

    // skip file header
    skip_header(data);
    
    // start to parse data into quadtree



    fclose(data);
}