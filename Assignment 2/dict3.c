#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
//#include "data.c"


int main(int argc, char * argv[]) {
    // check for sufficient arguments
    if (argc != 8) {
        printf("Insufficient arguments, please try again!\n");
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


    if (inRectangle(&test, &rect)) {
        printf("The point is in the rectangle!\n");
    }

    fclose(data);
}