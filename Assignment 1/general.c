#include <stdio.h>
#include <string.h>
#include "general.h"

struct node {
    int footpathID; // representing "key" in dictionary
    address_t address;
    clue_t clue;
    asset_t asset;
    double deltaz; // change in vertical distance
    double distance;
    double gradelin;
    int mccID;
    int mccID_int; 
    double rlmax;
    double rlmin;
    segside_t segside;
    int statusID;
    int streetID;
    int streetGroup;
    coordinates_t start;
    coordinates_t end;
    size_t node_size;
    footpath_t *next; // pointing to the next "key"
};

struct array {
    footpath_t **A;
    int size;
    int num_footpath;
};


