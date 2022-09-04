#include "data.h"
#include <stdio.h>
/*struct footpath {
    int footpath_id; // representing "key" in dictionary
    address_t address;
    clue_t clue_sa;
    asset_t asset_type;
    double deltaz; // change in vertical distance
    double distance;
    double gradel1n;
    int mcc_id;
    int mccid_int; 
    double rlmax;
    double rlmin;
    segside_t segside;
    int status_id;
    int street_id;
    int street_group;
    coordinates_t start;
    coordinates_t end;
    size_t node_size;
    footpath_t *next; // pointing to the next "key"
};*/

int inRectangle(point2D_t *point, rectangle2D_t *rect) {
    // Check for case where point lies on the bottom boundary, right boundary or inside the rectangle
    if (point->lat > rect->bot_left.lat && (point->lat <= rect->up_right.lat )) {
        if ((point->lon >= rect->bot_left.lon) && point->lon < rect->up_right.lon) {
            return 1;
        } else {
            printf("The point is outside, on the top or left boundary\n");
            return 0;
        }  
    } else {
        return 0;
    }
}