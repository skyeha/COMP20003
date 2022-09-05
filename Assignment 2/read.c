#include <stdio.h>
#include <stdlib.h>
#include "read.h"
// skip header line
void skip_header(FILE *file_in) {
    while(fgetc(file_in) != '\n');
} 