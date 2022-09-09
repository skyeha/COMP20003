#ifndef _DATA_H_
#define _DATA_H_

/* Declaration and definitions of constants */
#define MAX_ROW_SIZE 512
#define MAX_FIELD_SIZE 127
#define ASCII_VALUE_QUOTE 34

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
    footpath_t *head;
    footpath_t *foot;
} dictionary_t;

typedef struct {
    long double x;
    long double y;
} point2D_t; 

typedef struct {
    double x;
    double y;
} coordinates_t; 

typedef struct {
    point2D_t location;
    dictionary_t *dict;
} dataPoint_t;

typedef struct {
    point2D_t botLeft;
    point2D_t upRight;
} rectangle2D_t;



/* Functions prototypes */
quadtreeNode_t *createNode(rectangle2D_t *rect);
void insertPoint(quadtreeNode_t *root, point2D_t *point, footpath_t *fp);
rectangle2D_t makeRect(long double botLeftX, long double botLeftY, long double upRightX, long double upRightY);
int inRectangle(point2D_t *point, rectangle2D_t rect);
void searchPoint(coordinates_t *query, char *buffer, quadtreeNode_t *root, int flag, FILE* fileout);
void printQuad(quadtreeNode_t *node);
void toFileOut(FILE *fileOut, footpath_t *fp);
dictionary_t *putData(dictionary_t *dict, footpath_t *data);
quadtreeNode_t *freeTree(quadtreeNode_t *root);
dictionary_t *makeDict(void);
dictionary_t *insertAtFoot(dictionary_t *dict);
void freeDict(dictionary_t *dict);

/* Stage 4 */
void searchRange(point2D_t *queryBotL, point2D_t *queryUpR, quadtreeNode_t *root, char *buffer);
int overlapRect(point2D_t *queryBotL, point2D_t *queryUpR, quadtreeNode_t *root);
void pointInReg(quadtreeNode_t *root, int flag);
#endif