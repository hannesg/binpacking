/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Project
#include "double_vector.h"

// Self
#include "parse_instance.h"

const int MAX_LINE_LENGTH = 100;

double_vector *parse_instance(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if(file == NULL) {
        return NULL;
    }
    
    char buffer[MAX_LINE_LENGTH + 1];
    fgets(buffer, MAX_LINE_LENGTH, file);
    double_vector *vector = alloc_double_vector(atoi(buffer));
    
    int i;
    for(i = 0; i < vector->size; ++i) {
        fgets(buffer, MAX_LINE_LENGTH, file);
        if(strcmp(buffer, "") == 0) {
            printf("To few items\n");
            free_double_vector(vector);
            return NULL;
        }
        vector->values[i] = atof(buffer);
    }
    
    return vector;
}
