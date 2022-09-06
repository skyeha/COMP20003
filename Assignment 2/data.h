#ifndef _DATA_H_
#define _DATA_H_

/* Declaration and definitions of constants */
#define MAX_ROW_SIZE 512
#define MAX_FIELD_SIZE 127
#define NOT_ROOT 0
#define ROOT_NODE 1
#define INT_NODE 2

#define S_WEST 0
#define N_WEST 1
#define N_EAST 2
#define S_EAST 3


/* Declaration of data types and strcut */
typedef struct footpath footpath_t;
typedef struct quadtreeNode quadtreeNode_t;
typedef char address_t[MAX_FIELD_SIZE + 1];
typedef char clue_t[MAX_FIELD_SIZE + 1];
typedef char asset_t[MAX_FIELD_SIZE + 1];
typedef char segside_t[MAX_FIELD_SIZE + 1];

typedef struct {
    long double x;
    long double y;
} point2D_t; 

typedef struct {
    point2D_t location;
    footpath_t *footpath;
} dataPoint_t;

typedef struct {
    point2D_t botLeft;
    point2D_t upRight;
} rectangle2D_t;



// Functions prototypes
int inRectangle(point2D_t *point, rectangle2D_t *rect);
quadtreeNode_t *create_node(void);

#endif