/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

// Standard
#include <stdlib.h>
#include <stdio.h>

// Project
#include "print_uint_array.h"

// Self
#include "uint_vector.h"

uint_vector * alloc_uint_vector(unsigned int size)
{
    uint_vector *result = (uint_vector *) malloc(sizeof(uint_vector));
    result->size = size;
    result->values = (unsigned int *) malloc(sizeof(unsigned int) * size);

    return result;
}

void free_uint_vector(uint_vector * vector)
{
    if(vector == NULL) {
        return;
    }
    free(vector->values);
    free(vector);
}

void fill_uint_vector(uint_vector *vector, unsigned int value){
    unsigned int i;
    for(i = 0; i < vector->size; ++i) {
        vector->values[i] = value;
    }
}

void print_uint_vector(uint_vector *vector)
{
    print_uint_array(vector->values, vector->size);
}
