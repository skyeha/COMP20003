/* Declaration and definitions of constants */
#define MAX_ROW_SIZE 512
#define MAX_FIELD_SIZE 127

/* Declaration of data types and strcut */
typedef struct footpath footpath_t;
typedef char address_t[MAX_FIELD_SIZE + 1];
typedef char clue_t[MAX_FIELD_SIZE + 1];
typedef char asset_t[MAX_FIELD_SIZE + 1];
typedef char segside_t[MAX_FIELD_SIZE + 1];

typedef struct {
    double x;
    double y;
} point2D_t; 

typedef struct {
    double lat;
    double lon;
} coordinates_t;

typedef struct {
    point2D *point;
    footpath_t *footpath;
} dataPoint_t;

typedef struct {
    dataPoint_t *SW;
    dataPoint_t *NW;
    dataPoint_t *NE;
    dataPoint_t *SE;
} quadtreeNode;

typedef struct {
    point2D_t bottom_left;
    point2D_t upper_right;
} rectangle2D_t;