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
    
    // If num_point > 1, the pointer to quadrant will be pointing to address, otherwise, point to null.
    quadtreeNode_t *SW;
    quadtreeNode_t *NW;
    quadtreeNode_t *NE;
    quadtreeNode_t *SE;

};


quadtreeNode_t *create_node(rectangle2D_t *rect) {
    quadtreeNode_t *node;
    node = malloc(sizeof(*node));
    assert(node);
    node->rect.botLeft.x = (*rect).botLeft.x;
    node->rect.botLeft.y = (*rect).botLeft.y;
    node->rect.upRight.x = (*rect).upRight.x;
    node->rect.upRight.y = (*rect).upRight.y;

    node->point = NULL;

    // setting the quadrant pointers to null as num_point haven't exceeded 1
    node->NW = NULL;
    node->NE = NULL;
    node->SW = NULL;
    node->SE = NULL;

    return node;
}

void insertPoint(quadtreeNode_t *root, point2D_t *point) {
    // instance of the first node being inserted or node is empty
    if (!inRectangle(point, root->rect)) {
        // point is not in rectangle
        return;
    }

    if (root->point == NULL) {
        root->point = point;
        return;
    }

    long double midX = (root->rect.botLeft.x + root->rect.upRight.x) / 2.0,
                midY = (root->rect.botLeft.y + root->rect.upRight.y) / 2.0;

    // indicating point is on left half of the rectangle
    if (point->x <= midX) {
        // point lies in SW
        if (point->y < midY) {
            if (root->SW == NULL) {
                root->SW = create_node();
                insertPoint(root->SW, point);
            }
        } else if (midY <= point->y) {
            if (root->NW == NULL) {
                insertPoint(root->NW, point);
            }
        }
    } else if (point->x > midX) {
        if (point->y < midY) {
            if (root->SE == NULL) {
                root->SE = create_node();
                insertPoint(root->SE, point);
            }
        } else if (midY <= point->y) {
            if (root->NE == NULL) {
                root->NE = create_node();
                insertPoint(root->SE, point);
            }
        }
    }
    insertPoint(root, root->point);
}

int whichQuad(quadtreeNode_t *node, dataPoint_t *point) {
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

int inRectangle(point2D_t *point, rectangle2D_t rect) {
    // Check for case where point lies on the bottom boundary, right boundary or inside the rectangle
    if (point->x > rect.bot_left.x && (point->x <= rect.up_right.x )) {
        if ((point->y >= rect.bot_left.y) && point->y < rect.up_right.y) {
            return 1;
        } else {
            return 0;
        }  
    } else {
        return 0;
    }
} // Functions works fine


