#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "data.c"


int main(int argc, char * argv[]) {
    // creae outer rectangle space
    rectangle2D_t rect;
    
    // fill the coordinates for bottem left
    rect.bot_left.lon = 144.969;
    rect.bot_left.lat = -37.7975;

    // fill the coordinates for upper right
    rect.up_right.lon = 144.971;
    rect.up_right.lat = -37.7955;

    // test point;
    point2D_t test;
    scanf("%lf %lf", &test.lat, &test.lon);

    if (inRectangle) {
        printf("The point is in the rectangle!\n");
    }
}