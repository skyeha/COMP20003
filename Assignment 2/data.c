#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"

struct footpath {
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
    point2D_t start;
    point2D_t end;
    size_t node_size;
    footpath_t *next; // pointing to the next "key"
};

struct quadtreeNode {
    //store the rectangle;
    rectangle2D_t rect;
    dataPoint_t *point;
    int num_point; // keeping track of how many points inside the node

    // If num_point > 1, the pointer will be point to address, otherwise, it will point to null.
    quadtreeNode_t *SW;
    quadtreeNode_t *NW;
    quadtreeNode_t *NE;
    quadtreeNode_t *SE;
    quadtreeNode_t *origin; // point back to the internal node
    quadtreeNode_t *root; // point back to the very root node
};


quadtreeNode_t *create_node(char *argv[], int root) {
    quadtreeNode_t *node;
    node = malloc(sizeof(*node));
    assert(node);
    node->num_point = 0;
    if (root = ROOT_NODE) {
        node->rect.bot_left.lon = atof(argv[4]);
        node->rect.bot_left.lat = atof(argv[5]);
        node->rect.up_right.lon = atof(argv[6]);
        node->rect.up_right.lat = atof(argv[7]);
    } else if (is_root = INT_NODE) {
        node->rect.bot_left.lon = 
    }
    // setting the quadrant pointers to null as num_point haven't exceeded 1
    node->NW = NULL;
    node->NE = NULL;
    node->SW = NULL;
    node->SE = NULL;
    node->origin = NULL;
    node->root = node;

    return node;
}

void addPoint(quadtreeNode_t *node, FILE* file_in) {
    // instance of the first node being inserted or node is empty
    if (node->num_point == 0) {
        node->point = malloc(sizeof(*(node->point)));
        // insert function for parse data;
        node->num_point += 1;

    } else if (node->num_point == 1) {
        // need to split into four quadrant
        // insert quadrant split function
    }
}

void split_quadrant(quadtreeNode_t *node) {
    if (which_quad == S_WEST) {
        node->SW->point = malloc(sizeof(dataPoint_t));
        node->SW->num_point = 1;
        node->SW->origin = node;
        node->point = NULL; // as the root node no longer point to one datapoint
    } else if (which_quad == N_WEST) {
        node->NW->point = malloc(sizeof(dataPoint_t));
        node->NW->num_point = 1;
        node->NW->origin = node;
        node->point = NULL;
    } else if (which_quad == N_EAST) {
        node->NE->point = malloc(sizeof(dataPoint_t));
        node->NE->num_point = 1;
        node->NE->origin = node;
        node->point = NULL;
    } else if (which_quad == S_EAST) {
        node->SE->point = malloc(sizeof(dataPoint_t))
        node->NE->num_point = 1;
        node->NE->origin = 1;
        node->point = NULL;
    }

}
int which_quad(quadtreeNode_t *node, dataPoint_t *point) {
    long double mid_lon = (node->rect.bot_left.lon + node->rect.up_right.lon) / 2;
    long double mid_lat = (node->rect.bot_left.lat + node->rect.up_right.lat) / 2;
    
    if (inRectangle(point->location, node->rect.bot_left.lon, node->rect.bot_left.lat,
                                     mid_lon, mid_lat)){
        node->SW = malloc(sizeof(*(node->SW)));
        node->SW->rect.bot_left.lon = node->rect.bot_left.lon;
        node->SW->rect.bot_left.lat = node->rect.bot_left.lat;
        node->SW->rect.up_right.lon = mid_lon;
        node->SW->rect.up_right.lon = mid_lat;
        return 0;
    } else if (inRectangle(point->location, node->rect.bot_left.lon, mid_lat,
                                     mid_lon, node->rect.up_right.lat)) {
        node->NW = malloc(sizeof(*(node->NW)));
        node->SW->rect.bot_left.lon = node->rect.bot_left.lon;
        node->SW->rect.bot_left.lat = mid_lat;
        node->SW->rect.up_right.lon = mid_lon;
        node->SW->rect.up_right.lon = node->rect.up_right.lat;
        return 1;
    } else if (inRectangle(point->location, mid_lon, mid_lat,
                                     node->rect.up_right.lon, node->rect.up_right.lat)) {
        node->NE = malloc(sizeof(*(node->NE)));
        node->SW->rect.bot_left.lon = mid_lon;
        node->SW->rect.bot_left.lat = mid_lat;
        node->SW->rect.up_right.lon = node->rect.up_right.lon;
        node->SW->rect.up_right.lon = node->rect.up_right.lat;
        return 2;
    } else if (inRectangle(point->location, mid_lon, node->rect.bot_left.lat,
                                     node->rect.up_right.lon, mid_lat)) {
        node->SE = malloc(sizeof(*(node->SE)))
        node->SW->rect.bot_left.lon = mid_lon;
        node->SW->rect.bot_left.lat = node->rect.bot_left.lat;
        node->SW->rect.up_right.lon =node->rect.up_right.lon;
        node->SW->rect.up_right.lon = mid_lat;
        return 3;
    }
}

int inRectangle(point2D_t *point, point2D_t bot_left_lon, point2D_t bot_left_lat, point2D_t up_right_lon, point2D_t up_right_lat) {
    // Check for case where point lies on the bottom boundary, right boundary or inside the rectangle
    if (point->lon > bot_left_lon && (point->lon <= up_right_lon )) {
        if ((point->lat >= bot_left_lat) && point->lat < up_right_lat) {
            return 1;
        } else {
            return 0;
        }  
    } else {
        return 0;
    }
} // Functions works fine


