#include "general.h"
// function prototypes

array_t *build_array(void);

dictionary_t *make_dict(void);

void free_array(array_t *array, dictionary_t *dict);

void skip_header(FILE *file_in);

void read_data(array_t *array, dictionary_t *dict, FILE* file_in);

void insert_to_array(array_t *array, footpath_t *footpath);

//void insert_to_array(array_t *array, dictionary_t *dict);

void increase_size(array_t *array);

void reduce_size(array_t *arr);

void quicksort(array_t *array, int low, int high);

void do_quicksort(array_t *array);

int partition(array_t *array, int low, int high);

void swap(array_t *array, int i, int j);

void print_sorted_array(array_t *array);

int check_args(int num_argc, char *argv[]);

void record_search(array_t *array, char *query, FILE *file_out);
