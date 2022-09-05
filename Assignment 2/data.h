#ifndef _DATA_H_
#define _DATA_H_

/* Declaration and definitions of constants */
#define MAX_ROW_SIZE 512
#define MAX_FIELD_SIZE 127

/* Declaration of data types and strcut */
typedef struct footpath footpath_t;
typedef struct quadtreeNode quadtreeNode_t;
typedef char address_t[MAX_FIELD_SIZE + 1];
typedef char clue_t[MAX_FIELD_SIZE + 1];
typedef char asset_t[MAX_FIELD_SIZE + 1];
typedef char segside_t[MAX_FIELD_SIZE + 1];

typedef struct {
    long double lon;
    long double lat;
} point2D_t; 

typedef struct {
    point2D_t *point;
    footpath_t *footpath;
    quadtreeNode_t *original;
} dataPoint_t;

typedef struct {
    point2D_t bot_left;
    point2D_t up_right;
} rectangle2D_t;

// Functions prototypes
int inRectangle(point2D_t *point, rectangle2D_t *rect);
quadtreeNode_t *create_node(void);

#endif