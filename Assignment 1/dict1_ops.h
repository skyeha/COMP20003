#include "general.h"

// Function prototypes
dictionary_t *make_dict(void);

dictionary_t *insert_at_foot(dictionary_t *dict);

void skip_header(FILE *file_in);

void *read_data(dictionary_t *dict, FILE *file, array_t *array);

void address_lookup(dictionary_t *dict, char *query, FILE *file_out);

void free_dict(dictionary_t *dict);

int check_args(int num_argc, char *argv[]);
