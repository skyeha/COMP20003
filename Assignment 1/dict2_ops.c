#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dict2_ops.h"
#include "general.h"
#include "general.c"
#include <math.h>


array_t *build_array(void) {
    //allocate memory to create array
    array_t *array = malloc(sizeof(*array));
    //make sure memory is successully allocated
    assert(array);
    int size = INITIAL_SIZE;
    array->size = INITIAL_SIZE;

    // allocate memory for each pointer in the array
    array->A = malloc(sizeof(*(array->A)) * array->size);
    assert(array->A);
    array->num_footpath = 0;
    return array;
}

void free_array(array_t *array, dictionary_t *dict) {
    for (int i = 0; i < array->num_footpath; i++) {
        free(array->A[i]);
    }

    free(array->A);
    free(array);
    free(dict);
}

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

void read_data(array_t *array, dictionary_t *dict, FILE* file_in) {
    char buff[MAX_ROW_SIZE + 1];
    char *record,
         *token;
    assert(dict->head == NULL);
    footpath_t *current;
    while (fgets(buff, MAX_ROW_SIZE, file_in) != NULL) {
        insert_at_foot(dict);
        current = dict->foot;
        assert(current);
        
        record = strdup(buff);
        // temporary store memory allocated by strdup above
        // since strsep will make record pointing to null
        char *dup_str_addr = record;
        while ((token = strsep(&record, ",")) != NULL) {
            current->footpathID = atoi(token);

            token = strsep(&record, ",");
            strcpy(current->address, token);
            
            // special cases for "abc, def" in Clue
            token = strsep(&record, ",");
            if (strchr(token, ASCII_VALUE_QUOTE) != 0) {
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
        insert_to_array(array, current);
        free(dup_str_addr);
    }
}


// Insert footpath into each index of array of pointers. Code was inspired from Workshop Week 3
void insert_to_array(array_t* array, footpath_t *footpath) {
    increase_size(array);
    array->A[array->num_footpath] = footpath;
    (array->num_footpath)++;
}

// Increase size of array if insufficient space. Code was insipired from Workshop Week 3
void increase_size(array_t *array) {
    if (array->num_footpath == array->size) {
        array->size <<= 1;
        array->A = realloc(array->A, array->size* sizeof(*(array->A)));
        assert(array->A);
    }
}

// Sort the array base on gradelin
void quicksort(array_t *array, int low, int high) {
    //printf("1. Reached this line\n");
    int pi;
    if (low < high) {
        pi = partition(array, low, high);
        quicksort(array, low, pi - 1);
        quicksort(array, pi + 1, high);
    }
}

int partition(array_t *array, int low, int high) {
    //printf("%lf\n", (array->A[high]->gradelin));
    //printf("flag!\n");
    double pivot = array->A[high]->gradelin;

    //printf("2. Reached partition function!\n");
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        //printf("3. Reached inside for loop!\n");
        if (array->A[j]->gradelin <= pivot) {
            i++;
            swap(array, i, j);
        }
    }
    //printf("3. Reach after for loop");
    swap(array, i + 1, high);
    return (i + 1);
}

void swap(array_t *array, int i, int j) {
    footpath_t *tmp ;
    tmp = array->A[i];
    array->A[i] = array->A[j];
    array->A[j] = tmp;
}

void print_sorted_array(array_t *array) {
    for (int i = 0; i < array->num_footpath; i++) {
        printf("Footpath ID: %d\n", array->A[i]->footpathID);
        printf("Gradelin: %lf\n", array->A[i]->gradelin);
        printf("=================\n");
    }
}

void do_quicksort(array_t *array) {
    int low = 0;
    quicksort(array, low, array->num_footpath - 1);
}


// Reduced the size if we didn't use all the allocated memory. Code was inspired from Workshop Week 3
void reduce_size(array_t *array) {
	if (array->size != array->num_footpath) {
		// the new size should be at least INIT_SIZE
		array->size = array->num_footpath > INITIAL_SIZE ? array->num_footpath : INITIAL_SIZE;
		array->A = realloc(array->A, array->size * sizeof(*(array->A)));
		assert(array->A);
	}
}


int check_args(int num_argc, char *argv[]) {
    if (num_argc < 3 || strcmp(argv[1], "2") != 0) {
        printf("Incorrect or/and insufficient arguments!\n");
        return 0;
    }
}

void record_search(array_t *array, char *query, FILE *file_out) {
    double search_key = atof(query);
    int index = 0;
    double closest = fabs((array->A[index]->gradelin) - search_key);


    footpath_t **A = array->A;

    for (int i = 1; i < array->num_footpath; i++) {
        double dif = fabs(array->A[i]->gradelin - search_key);
        if  ( dif < closest) {
            closest = dif;
            index = i;
        }
    }
    printf("%s --> %.1lf\n", query, A[index]->gradelin);

    fprintf(file_out, "%s\n", query);
    fprintf(file_out, "--> footpath_id: %d || ", A[index]->footpathID);
    fprintf(file_out, "address: %s || ", A[index]->address);
    fprintf(file_out, "clue_sa: %s || ", A[index]->clue);
    fprintf(file_out, "asset_type: %s || ", A[index]->asset);
    fprintf(file_out, "deltaz: %.2lf || ", A[index]->deltaz);
    fprintf(file_out, "distance: %.2lf || ", A[index]->distance);
    fprintf(file_out, "grade1in: %.1lf || ", A[index]->gradelin);
    fprintf(file_out, "mcc_id: %d || ", A[index]->mccID);
    fprintf(file_out, "mccid_int: %d || ", A[index]->mccID_int);
    fprintf(file_out, "rlmax: %.2lf || ", A[index]->rlmax);
    fprintf(file_out, "rlmin: %.2lf || ", A[index]->rlmin);
    fprintf(file_out, "segside: %s || ", A[index]->segside);
    fprintf(file_out, "statusid: %d || ", A[index]->statusID);
    fprintf(file_out, "streetid: %d || ", A[index]->streetID);
    fprintf(file_out, "street_group: %d || ", A[index]->streetGroup);
    fprintf(file_out, "start_lat: %lf || ", A[index]->start.lat);
    fprintf(file_out, "start_lon: %lf || ", A[index]->start.lon);
    fprintf(file_out, "end_lat: %lf || ", A[index]->end.lat);
    fprintf(file_out, "end_lon: %lf ||\n", A[index]->end.lon);

}