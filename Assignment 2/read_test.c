#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "data.h"
// skip header line
void skip_header(FILE *file_in) {
    while(fgetc(file_in) != '\n');
} 

void *read_data(FILE* file, quadtreeNode_t *node) {
    char buff[MAX_ROW_SIZE + 1];
    char *record,
         *token;
    footpath_t *current;
    while (fgets(buff, MAX_ROW_SIZE, file) != NULL) {
        record = strdup(buff);
        char *dup_str_addr = record;
        //printf("record before: %s\n", record);
        while ((token = strsep(&record, ",")) != NULL) {
            current->footpathID = atoi(token);

            token = strsep(&record, ",");
            current->start.lat = atof(token);

            token = strsep(&record, ",");
            current->start.lon = atof(token);

            token = strsep(&record, ",");
            current->end.lat = atof(token);

            token = strsep(&record, ",");
            current->end.lon = atof(token);
        }
        if (inRectangle(&(current.start), node->rect)) {
            addPoint();
        }
        if (inRectangle(&(current.end), node->rect)) {
            addPoint();
        }

        
        free(dup_str_addr);
    }
}