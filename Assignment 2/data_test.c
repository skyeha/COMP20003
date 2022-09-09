#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "data.h"

struct footpath {
    int footpath_id;
    address_t address;
    clue_t clue_sa;
    asset_t asset_type;
    double deltaz; 
    double distance;
    double grade1in;
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
    footpath_t *next; // to store data that share the same point
};

struct quadtreeNode {
    //store the rectangle;
    rectangle2D_t rect;
    dataPoint_t *point;
    int num_point;
    
    // If num_point > 1, the pointer to quadrant will be pointing to address, otherwise, point to null.
    quadtreeNode_t *SW;
    quadtreeNode_t *NW;
    quadtreeNode_t *NE;
    quadtreeNode_t *SE;

};

quadtreeNode_t *createNode(rectangle2D_t *rect) {
    quadtreeNode_t *node;
    node = malloc(sizeof(*node));
    assert(node);
    node->rect.botLeft.x = rect->botLeft.x;
    node->rect.botLeft.y = rect->botLeft.y;
    node->rect.upRight.x = rect->upRight.x;
    node->rect.upRight.y = rect->upRight.y;

    // keeping track of how many points in the internal node
    node->num_point = 0;
    
    node->point = NULL;

    // setting the quadrant pointers to null
    node->NW = NULL;
    node->NE = NULL;
    node->SW = NULL;
    node->SE = NULL;

    return node;
}

// code was taken from Assignment 1 of COMP20003
dictionary_t *makeDict(void) {
    dictionary_t *dict; 
    dict = (dictionary_t *)malloc(sizeof(*dict));
    //make sure memory is succesfully allocated
    assert(dict != NULL);
    dict->head = dict->foot = NULL;
    return dict;
}

// code was taken from Assignment 1 of COMP20003
dictionary_t *insertAtFoot(dictionary_t *dict) {
    footpath_t *new;
    new = (footpath_t *)malloc(sizeof(*new));
    assert(dict != NULL && new != NULL);
    new->next = NULL;

    if (dict->head == NULL && dict->foot == NULL) {
        /* first insertion into the dictionary */
        dict->head = dict->foot = new;
    } else {
        dict->foot->next = new;
        dict->foot = new;
    }
    return dict;
}  

// part of code was inspire from geeksforgeeks (https://www.geeksforgeeks.org/quad-tree/)
void insertPoint(quadtreeNode_t *root, point2D_t *point, footpath_t *fp) {
    // check if the point is in the rectangle, reject immidiately if not inside.
    if (!inRectangle(point, root->rect)) {
        return;
    }
    // instance of the a leaf node
    if (root->num_point == 0 && root->point == NULL) {
        root->point = malloc(sizeof(*(root->point)));
        root->point->location.x = point->x;
        root->point->location.y = point->y;
        root->point->dict = makeDict();
        root->point->dict = putData(root->point->dict, fp);
        root->num_point = 1;
        return;
    }

    // compute middle value for width and lenght of rectangle
    long double midX = (root->rect.botLeft.x + root->rect.upRight.x) / 2.0,
                midY = (root->rect.botLeft.y + root->rect.upRight.y) / 2.0;

    rectangle2D_t rect;
    if (root->point->location.x == point->x && root->point->location.y == point->y) {
        if (root->point->dict->head->footpath_id != fp->footpath_id) {
            root->point->dict = putData(root->point->dict, fp);
            return;
        }
        // this is for cases when reinsert datapoint as the leaf node becomes internal node
        if (point->x <= midX) {
            if (point->y < midY) {
                if (root->SW == NULL) {
                    rect = makeRect(root->rect.botLeft.x, root->rect.botLeft.y, midX, midY);
                    root->SW = createNode(&rect);
                }
                insertPoint(root->SW, point, fp);
            } else if (midY <= point->y) {
                if (root->NW == NULL) {
                    rect = makeRect(root->rect.botLeft.x, midY, midX, root->rect.upRight.y);
                    root->NW = createNode(&rect);
                }
                insertPoint(root->NW, point, fp);
            }
        } else if (point->x > midX) {
            if (point->y < midY) {
                if (root->SE == NULL) {
                    rect = makeRect(midX, root->rect.botLeft.y, root->rect.upRight.x, midY);
                    root->SE = createNode(&rect);
                }
                insertPoint(root->SE, point, fp);
            } else if (midY <= point->y) {
                if (root->NE == NULL) {
                    rect = makeRect(midX, midY, root->rect.upRight.x, root->rect.upRight.y);
                    root->NE = createNode(&rect);
                }
                insertPoint(root->NE, point, fp);
            }
        }
    } 
    // deciding on which quadrant should the new datapoint lies
    else {
        if (point->x <= midX) {
            // point lies in SW
            if (point->y < midY) {
                // if quadrant pointer is null, it's yet to have a datapoint
                if (root->SW == NULL) {
                    rect = makeRect(root->rect.botLeft.x, root->rect.botLeft.y, midX, midY);
                    root->SW = createNode(&rect);
                    insertPoint(root->SW, point, fp);
                    // reinsert the point since there's a new point
                    insertPoint(root, &(root->point->location), root->point->dict->head);
                    root->num_point++;
                } 
                //the quadrant being not null means that there's already re-insertion, hence no need to repeat
                else if (root->SW != NULL) {
                    insertPoint(root->SW, point, fp);
                }  
            } else if (midY <= point->y) {
                if (root->NW == NULL) {
                    rect = makeRect(root->rect.botLeft.x, midY, midX, root->rect.upRight.y);
                    root->NW = createNode(&rect);
                    insertPoint(root->NW, point, fp);
                    insertPoint(root, &(root->point->location), root->point->dict->head);
                    root->num_point++;
                } else if (root->NW != NULL) {
                    insertPoint(root->NW, point, fp);
                }
            }
        } else if (point->x > midX) {
            if (point->y < midY) {
                if (root->SE == NULL) {
                    rect = makeRect(midX, root->rect.botLeft.y, root->rect.upRight.x, midY);
                    root->SE = createNode(&rect);
                    insertPoint(root->SE, point, fp);
                    insertPoint(root, &(root->point->location), root->point->dict->head);
                    root->num_point++;
                } else if(root->SE != NULL) {
                    insertPoint(root->SE, point, fp);
                }
            } else if (midY <= point->y) {
                if (root->NE == NULL) {
                    rect = makeRect(midX, midY, root->rect.upRight.x, root->rect.upRight.y);
                    root->NE = createNode(&rect);
                    insertPoint(root->NE, point, fp);
                    insertPoint(root, &(root->point->location), root->point->dict->head);
                    root->num_point++;
                } else if (root->NE != NULL) {
                    insertPoint(root->NE, point, fp);
                }
            }
        }
    }
}

// insert footpath into the dictionary that is stored within every node
dictionary_t *putData(dictionary_t *dict, footpath_t *data) {
    dict = insertAtFoot(dict);
    footpath_t *fp;
    fp =  dict->foot; 

    fp->footpath_id = data->footpath_id;
    strcpy(fp->address, data->address);
    strcpy(fp->clue_sa, data->clue_sa);
    strcpy(fp->asset_type, data->asset_type);
    fp->deltaz = data->deltaz;
    fp->distance = data->distance;
    fp->grade1in = data->grade1in;
    fp->mcc_id = data->mcc_id;
    fp->mccid_int = data->mccid_int;
    fp->rlmax = data->rlmax;
    fp->rlmin = data->rlmin;
    strcpy(fp->segside, data->segside);
    fp->status_id = data->status_id;
    fp->street_id = data->street_id;
    fp->street_group = data->street_group;
    fp->start.x = data->start.x;
    fp->start.y = data->start.y;
    fp->end.x = data->end.x;
    fp->end.y = data->end.y;
    fp->next = NULL;
    return dict;
}

// helper function to create rectangle for instances when inserting new datapoints
rectangle2D_t makeRect(long double botLeftX, long double botLeftY, long double upRightX, long double upRightY) {
    rectangle2D_t rect;
    rect.botLeft.x = botLeftX;
    rect.botLeft.y = botLeftY;
    rect.upRight.x = upRightX;
    rect.upRight.y = upRightY;
    return rect;
}

// free all the allocated memory of the quadTree
quadtreeNode_t *freeTree(quadtreeNode_t *root) {
    // free individual node
    if (root->NE != NULL) {
        root->NE = freeTree(root->NE);
    }
    
    if (root->SE != NULL) {
        root->SE = freeTree(root->SE);
    }

    if (root->NW != NULL) {
        root->NW = freeTree(root->NW);
    }

    if (root->SW != NULL) {
        root->SW = freeTree(root->SW);
    }

    if (root->NE == NULL && root->SE == NULL && root->NW == NULL && root->SW == NULL) {
        freeDict(root->point->dict);
        free(root->point);
        root->point = NULL;
        free(root);
        root = NULL;
    }
    return root;
}

// free the dictionary (linked list)
void freeDict(dictionary_t *dict) {
    footpath_t  *current,
                *previous;
    assert(dict != NULL);
    current = dict->head;
    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }
    free(dict);
}

void printQuad(quadtreeNode_t *node) {
    printf("footpath: %d\n", node->SW->NW->NE->SW->SW->point->dict->head->footpath_id);
    //printf("footpath: %d\n", node->SW->NW->NE->SW->SW->point->dict->head->next->footpath_id);
}

// checking if a point is in the rectangle
int inRectangle(point2D_t *point, rectangle2D_t rect) {
    // Check for case where point lies on the bottom boundary, right boundary or inside the rectangle
    if (point->x > rect.botLeft.x && (point->x <= rect.upRight.x )) {
        if ((point->y >= rect.botLeft.y) && point->y < rect.upRight.y) {
            return 1;
        } else {
            return 0;
        }  
    }
    return 0;
} 

// search point that is close to the query
void searchPoint(coordinates_t *query, char *buffer, quadtreeNode_t *root, int flag, FILE *fileOut) {
    // temporarily converting the query into point for ease of checking in the rectangle   
    point2D_t sub;
    sub.x = query->x;
    sub.y = query->y;
    if (!inRectangle(&sub, root->rect)) {
        return;
    }
    if (flag == 0) {
        printf("%s -->", buffer);
        fprintf(fileOut,"%s\n", buffer);
        flag = 1;
    }

    footpath_t *fp;

    /* check where the query lies in the quadrant and also if it's in 4 other quadrants (if any) once upoon reaching a leaf node, it's mean that the query is closest to that particular leaf node
       otherwise, the query is not in the tree */
    if (root->NW != NULL && inRectangle(&sub, root->NW->rect)) {
        if (root->NW->num_point > 1) {
            printf(" NW");
            searchPoint(query, buffer, root->NW, flag, fileOut);
        } else {
            printf(" NW\n");
            fp = root->NW->point->dict->head;
            while (fp != NULL) {
                toFileOut(fileOut, fp);
                fp = fp->next;
            }
        }
    } else if (root->NE != NULL && inRectangle(&sub, root->NE->rect)) {
        if (root->NE->num_point > 1) {
            printf(" NE");
            searchPoint(query, buffer, root->NE, flag, fileOut);
        } else {
            printf(" NE\n");
            fp = root->NE->point->dict->head;
            while (fp != NULL) {
                toFileOut(fileOut, fp);
                fp = fp->next;
            }
        }
    } else if (root->SW != NULL && inRectangle(&sub, root->SW->rect)) {
        if (root->SW->num_point > 1) {
            printf(" SW");
            searchPoint(query, buffer, root->SW, flag, fileOut);
        } else {
            printf(" SW\n");
            fp = root->SW->point->dict->head;
            while (fp != NULL) {
                toFileOut(fileOut, fp);
                fp = fp->next;
            }
        }
    } else if (root->SE != NULL && inRectangle(&sub, root->SE->rect)) {
        if (root->SE->num_point > 1) {
            printf(" SE");
            searchPoint(query, buffer, root->SE, flag, fileOut);
        } else {
            printf(" SE\n");
            fp = root->SE->point->dict->head;
            while (fp != NULL) {
                toFileOut(fileOut, fp);
                fp = fp->next;
            }
        }
    }
}


void searchRange(point2D_t *queryBotL, point2D_t *queryUpR, quadtreeNode_t *root, char buffer, int flag) {
    if (overlapRect(queryBotL, queryUpR, &(root->rect)) && flag == 1) {
        printf("%s -->", buffer);
        flag = 0;
    } else {
        return;
    }
    
    if (root->NW != NULL) {
        if (overlapRect(queryBotL, queryUpR, &(root->NW->rect))) {
            printf(" NW");
            searchRange(queryBotL, queryUpR, root->NW, buffer, flag);
        }
    }

    if (root->NE != NULL) {
        if (overlapRect(queryBotL, queryUpR, &(root->NE->rect))) {
            printf(" NE");
            searchRange(queryBotL, queryUpR, root->NE, buffer, flag);
        }
    }

    if (root->SE != NULL) {
        if (overlapRect(queryBotL, queryUpR, &(root->SE->rect))) {
            printf(" SE");
            searchRange(queryBotL, queryUpR, root->SE, buffer, flag);
        }
    }

    if (root->SW != NULL) {
        if (overlapRect(queryBotL, queryUpR, &(root->SW->rect))) {
            printf(" SW");
            searchRange(queryBotL, queryUpR, root->SW, buffer, flag);
        }
    }
}

int overlapRect(point2D_t *queryBotL, point2D_t *queryUpR, rectangle2D_t *rect) {
    
    if (rect->botLeft.x > queryUpR->x || rect->upRight.x < queryBotL->x) {
        //printf("Not overlap!\n");
        // the rectangle do not overlap
        return 0;
    }
    if (rect->botLeft.y > queryUpR->y || rect->upRight.y < queryBotL->y) {
        // the rectangle do not overlap
        //printf("Not overlap!\n");
        return 0;
    }
    return 1;
} 


// printing to outFile
void toFileOut(FILE *fileOut, footpath_t *fp) {
    fprintf(fileOut, "--> footpath_id: %d || ", fp->footpath_id);
    fprintf(fileOut, "address: %s || ", fp->address);
    fprintf(fileOut, "clue_sa: %s || ", fp->clue_sa);
    fprintf(fileOut, "asset_type: %s || ", fp->asset_type);
    fprintf(fileOut, "deltaz: %.2lf || ", fp->deltaz);
    fprintf(fileOut, "distance: %.2lf || ", fp->distance);
    fprintf(fileOut, "grade1in: %.1lf || ", fp->grade1in);
    fprintf(fileOut, "mcc_id: %d || ", fp->mcc_id);
    fprintf(fileOut, "mccid_int: %d || ", fp->mccid_int);
    fprintf(fileOut, "rlmax: %.2lf || ", fp->rlmax);
    fprintf(fileOut, "rlmin: %.2lf || ", fp->rlmin);
    fprintf(fileOut, "segside: %s || ", fp->segside);
    fprintf(fileOut, "statusid: %d || ", fp->status_id);
    fprintf(fileOut, "streetid: %d || ", fp->street_id);
    fprintf(fileOut, "street_group: %d || ", fp->street_group);
    fprintf(fileOut, "start_lat: %Lf || ", fp->start.y);
    fprintf(fileOut, "start_lon: %Lf || ", fp->start.x);
    fprintf(fileOut, "end_lat: %Lf || ", fp->end.y);
    fprintf(fileOut, "end_lon: %Lf ||\n", fp->end.x);
}