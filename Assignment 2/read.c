#include <stdio.h>
#include <stdlib.h>
#include "read.h"
// skip header line
void skip_header(FILE *file_in) {
    while(fgetc(file_in) != '\n');
} 

void *read_data(FILE* file) {
    char buff[MAX_ROW_SIZE + 1];
    char *record,
         *token;
    footpath_t current;
    while (fgets(buff, MAX_ROW_SIZE, file) != NULL) {
        assert(current);
        
        record = strdup(buff);
        
        // temporary store memory allocated by strdup above
        // since strsep will make record become null
        char *dup_str_addr = record;
        //printf("record before: %s\n", record);
        while ((token = strsep(&record, ",")) != NULL) {
            current->footpathID = atoi(token);

            token = strsep(&record, ",");
            strcpy(current->address, token);
            
            // special cases for "abc, def" in Clue
            token = strsep(&record, ",");
            if (strchr(token, ASCII_VALUE_QUOTE) != 0) {
                strcpy(current->clue, &token[1]);
                token = strsep(&record, ",");
                strcat(current->clue, ",");
                //int token_len = strlen(token);
                strncat(current->clue, token, strlen(token) - 1);
            } else {
                strcpy(current->clue, token);
            }

            token = strsep(&record, ",");
            strcpy(current->asset, token);

            token = strsep(&record, ",");
            current->deltaz = atof(token);

            token = strsep(&record, ",");
            current->distance = atof(token);

            token = strsep(&record, ",");
            current->gradelin = atof(token);

            token = strsep(&record, ",");
            current->mccID = atoi(token);

            token = strsep(&record, ",");
            current->mccID_int = atoi(token);

            token = strsep(&record, ",");
            current->rlmax = atof(token);
            
            token = strsep(&record, ",");
            current->rlmin = atof(token);

            token = strsep(&record, ",");
            strcpy(current->segside, token);

            token = strsep(&record, ",");
            current->statusID = atoi(token);

            token = strsep(&record, ",");
            current->streetID = atoi(token);

            token = strsep(&record, ",");
            current->streetGroup = atoi(token);

            token = strsep(&record, ",");
            current->start.lat = atof(token);

            token = strsep(&record, ",");
            current->start.lon = atof(token);

            token = strsep(&record, ",");
            current->end.lat = atof(token);

            token = strsep(&record, ",");
            current->end.lon = atof(token);
        }
        free(dup_str_addr);
    }
}