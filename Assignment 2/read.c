#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "data.h"
#include "data_test.c"

/* both of these code where taken from Assignment 1 of COMP20003 with little modifications to suit this assignment */
void skipHeader(FILE *file_in) {
    while(fgetc(file_in) != '\n');
} 

void readData(FILE* file, quadtreeNode_t *root) {
    char buff[MAX_ROW_SIZE + 1];
    char *record,
         *token;
    footpath_t current;
    while (fgets(buff, MAX_ROW_SIZE, file) != NULL) {
        record = strdup(buff);
        char *dup_str_addr = record;
        //printf("record before: %s\n", record);
        while ((token = strsep(&record, ",")) != NULL) {
            current.footpath_id = atoi(token);
            
            token = strsep(&record, ",");
            strcpy(current.address, token);
            
            // special cases for "abc, def" in Clue
            token = strsep(&record, ",");
            if (strchr(token, ASCII_VALUE_QUOTE) != 0) {
                strcpy(current.clue_sa, &token[1]);
                token = strsep(&record, ",");
                strcat(current.clue_sa, ",");
                //int token_len = strlen(token);
                strncat(current.clue_sa, token, strlen(token) - 1);
            } else {
                strcpy(current.clue_sa, token);
            }

            token = strsep(&record, ",");
            strcpy(current.asset_type, token);

            token = strsep(&record, ",");
            current.deltaz = atof(token);

            token = strsep(&record, ",");
            current.distance = atof(token);

            token = strsep(&record, ",");
            current.grade1in = atof(token);

            token = strsep(&record, ",");
            current.mcc_id = atoi(token);

            token = strsep(&record, ",");
            current.mccid_int = atoi(token);

            token = strsep(&record, ",");
            current.rlmax = atof(token);
            
            token = strsep(&record, ",");
            current.rlmin = atof(token);

            token = strsep(&record, ",");
            strcpy(current.segside, token);

            token = strsep(&record, ",");
            current.status_id = atoi(token);

            token = strsep(&record, ",");
            current.street_id = atoi(token);

            token = strsep(&record, ",");
            current.street_group = atoi(token);

            token = strsep(&record, ",");
            current.start.y = atof(token);

            token = strsep(&record, ",");
            current.start.x = atof(token);

            token = strsep(&record, ",");
            current.end.y = atof(token);

            token = strsep(&record, ",");
            current.end.x = atof(token);
        }
        insertPoint(root, &(current.start), &current);
        insertPoint(root, &(current.end), &current);
        free(dup_str_addr);
    }
}