//definition of constants and data types
#ifndef _GENERAL_H_
#define _GENERAL_H_

#define INITIAL_SIZE 2
#define MAX_ROW_SIZE 512
#define ASCII_VALUE_QUOTE 34
#define MAX_FIELD_SIZE 127

// declarations of data types structs
typedef char address_t[MAX_FIELD_SIZE + 1];
typedef char clue_t[MAX_FIELD_SIZE + 1];
typedef char asset_t[MAX_FIELD_SIZE + 1];
typedef char segside_t[MAX_FIELD_SIZE + 1];
typedef struct node footpath_t;
typedef struct array array_t;

typedef struct {
    double lat;
    double lon;
} coordinates_t;

typedef struct {
    footpath_t *head;
    footpath_t *foot;
    //size_t dict_size;
} dictionary_t;

// Functions prototypes
#endif