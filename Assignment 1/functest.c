#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_CHAR 512
#define QUOTE_ASCII 34

dictionary_t *make_dict(void) {
    dictionary_t *dict; 
    dict = (dictionary_t *)malloc(sizeof(*dict));
    assert(dict != NULL);
    dict->head = dict->foot = NULL;
    return dict;
}

dictionary_t *insert_at_foot(dictionary_t *test) {
    node_t *new;
    new = (node_t *)malloc(sizeof(*new));
    assert(test != NULL && new != NULL);
    new->next = NULL;

    if (test->head == NULL && test->foot == NULL) {
        /* first insertion into the dictionary */
        test->head = test->foot = new;
    } else {
        test->foot->next = new;
        test->foot = new;
    }
    test->dict_size += sizeof(*new);
    return test;
}

void read_data(dictionary_t **test, FILE *file) {
    printf("Address stored in test deref: %p\n\n", (*test));
    // skip header line
    char header[MAX_CHAR + 1];
    fgets(header, MAX_CHAR, file);
    printf("Header line: %s\n", header);

    char buff[MAX_CHAR + 1];
    char *record,
         *token;
    assert((*test)->head == NULL);
    node_t *current;
    //assert(fgets(buff, MAX_CHAR, file) != NULL);
    while (fgets(buff, MAX_CHAR, file) != NULL) {
        insert_at_foot((*test));
        assert((*test)->head);
        printf("============================\n");
        printf("Address stored in test.head: %p\n\n", (*test)->head);
        current = (*test)->foot;
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
            if (strchr(token, QUOTE_ASCII) != 0) {
                strcat(current->clue, &token[1]);
                token = strsep(&record, ",");
                strcat(current->clue, ",");
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
    printf("Address stored in test: %p\n", test);
    printf("Address of test derefferenced: %p\n", (*test));
    printf("Address stored in dict.head: %p\n", (*test)->head);
    assert((*test)->head);
}

void address_lookup(dictionary_t **dict, char *query, FILE* file_out) {
    node_t *footpath = (*dict)->head;
    assert(footpath);
    //count number of footpath found
    int footpath_founded = 0;

    while(footpath != NULL) {
        if (strcmp(footpath->address, query) == 0) {
            fprintf(file_out, "%s\n", query);
            footpath_founded++;
        }
        footpath = footpath->next;
    }


    //displaying results to stdout.
    if (footpath_founded != 0) {
        printf("%s --> %d\n", query, footpath_founded);
    } else {
        printf("%s --> NOTFOUND\n", query);
    }
}

void free_dict(dictionary_t *dict) {
    node_t* pointer;
    while (dict->head != NULL) {
        pointer = dict->head;
        dict->head = dict->head->next;
        free(pointer);
    }
    free(dict);
}