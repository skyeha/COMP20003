#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dict1_ops.h"
#include "general.h"
#include "general.c"


// structs definitions

/*struct node {
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
}; */


// functions definitions
dictionary_t *make_dict(void) {
    dictionary_t *dict; 
    dict = (dictionary_t *)malloc(sizeof(*dict));
    //make sure memory is succesfully allocated
    assert(dict != NULL);
    dict->head = dict->foot = NULL;
    return dict;
}

dictionary_t *insert_at_foot(dictionary_t *dict) {
    footpath_t *new;
    new = (footpath_t *)malloc(sizeof(*new));
    assert(dict != NULL && new != NULL);
    new->next = NULL;
    new->node_size = 0;

    if (dict->head == NULL && dict->foot == NULL) {
        /* first insertion into the dictionary */
        dict->head = dict->foot = new;
    } else {
        dict->foot->next = new;
        dict->foot = new;
    }
    return dict;
}  

void skip_header(FILE *file_in) {
    while(fgetc(file_in) != '\n');
} 

void *read_data(dictionary_t *dict, FILE* file, array_t *array) {
    char buff[MAX_ROW_SIZE + 1];
    char *record,
         *token;
    assert(dict->head == NULL);
    footpath_t *current;
    while (fgets(buff, MAX_ROW_SIZE, file) != NULL) {
        dict = insert_at_foot(dict);
        current = dict->foot;
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

void address_lookup(dictionary_t *dict, char *query, FILE* file_out) {
    footpath_t *footpath = dict->head;
    assert(footpath);
    //count number of footpath found
    int footpath_founded = 0;
    int flag = 1;

    while(footpath != NULL) {
        if (strcmp(footpath->address, query) == 0) {
            if (flag) {
                fprintf(file_out, "%s\n", query);
                flag = 0;
            }
            fprintf(file_out, "--> footpath_id: %d || ", footpath->footpathID);
            fprintf(file_out, "address: %s || ", footpath->address);
            fprintf(file_out, "clue_sa: %s || ", footpath->clue);
            fprintf(file_out, "asset_type: %s || ", footpath->asset);
            fprintf(file_out, "deltaz: %.2lf || ", footpath->deltaz);
            fprintf(file_out, "distance: %.2lf || ", footpath->distance);
            fprintf(file_out, "grade1in: %.1lf || ", footpath->gradelin);
            fprintf(file_out, "mcc_id: %d || ", footpath->mccID);
            fprintf(file_out, "mccid_int: %d || ", footpath->mccID_int);
            fprintf(file_out, "rlmax: %.2lf || ", footpath->rlmax);
            fprintf(file_out, "rlmin: %.2lf || ", footpath->rlmin);
            fprintf(file_out, "segside: %s || ", footpath->segside);
            fprintf(file_out, "statusid: %d || ", footpath->statusID);
            fprintf(file_out, "streetid: %d || ", footpath->streetID);
            fprintf(file_out, "street_group: %d || ", footpath->streetGroup);
            fprintf(file_out, "start_lat: %lf || ", footpath->start.lat);
            fprintf(file_out, "start_lon: %lf || ", footpath->start.lon);
            fprintf(file_out, "end_lat: %lf || ", footpath->end.lat);
            fprintf(file_out, "end_lon: %lf ||\n", footpath->end.lon);
            footpath_founded++;
        }
        footpath = footpath->next;
    }

    //displaying results to stdout.
    if (footpath_founded != 0) {
        printf("%s --> %d\n", query, footpath_founded);
    } else {
        fprintf(file_out, "%s\n", query);
        printf("%s --> NOTFOUND\n", query);
    }
}

void free_dict(dictionary_t *dict) {
    footpath_t* pointer;
    while (dict->head != NULL) {
        pointer = dict->head;
        dict->head = dict->head->next;
        free(pointer);
    }
    free(dict);
}

int check_args(int num_argc, char *argv[]) {
    if (num_argc < 3 || strcmp(argv[1], "1") != 0) {
        printf("Incorrect or/and insufficient arguments!\n");
        exit(EXIT_FAILURE);
    }
}