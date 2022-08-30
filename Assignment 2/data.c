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
    coordinates_t start;
    coordinates_t end;
    size_t node_size;
    footpath_t *next; // pointing to the next "key"
};
