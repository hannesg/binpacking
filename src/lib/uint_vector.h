/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#ifndef UINT_VECTOR_H
#define UINT_VECTOR_H

#include "types.h"

struct uint_vector_s {
    unsigned int size;
    unsigned int * values;
};

/**
 * Allocate an unsigned integer vector with the size @p size.
 */
uint_vector *alloc_uint_vector(unsigned int size);

/**
 * Free the unsigned int vector @p vector.
 */
void free_uint_vector(uint_vector *vector);

/**
 * Fill the unsigned integer vector @p vector with the value @p value.
 */
void fill_uint_vector(uint_vector *vector, unsigned int value);

/**
 * Print a formatted output of the vector values.
 */
void print_uint_vector(uint_vector *vector);

inline unsigned int uint_vector_elem(uint_vector *vector, unsigned int item);

#endif
