/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#ifndef DOUBLE_VECTOR_H
#define DOUBLE_VECTOR_H

#include "types.h"

struct double_vector_s {
    unsigned int size;
    double * values;
};

/**
 * Allocate a vector of @p size doubles.
 */
double_vector *alloc_double_vector(unsigned int size);

/**
 * Free the double vector @p vector.
 */
void free_double_vector(double_vector *vector);

/**
 * Print a formatted output of the vector values.
 */
void print_double_vector(double_vector *vector);

/** 
 * Fill the double vector @p vector with the value @p value.
 */
void fill_double_vector(double_vector *vector, double value);

uint_vector *double_vector_order(double_vector *vector);

/**
 * Calculates the minimum of all items in the vector @p x
 */
double vector_min(double_vector *x);

/**
 * Calculates the sum of all entries of vector @p x
 */
double vector_sum(double_vector *x);

/**
 * Calculates the scalar product of @p a and @p b.
 */
double vector_scalar_mult(double_vector *a, double_vector *b);

/**
 * Calculates a + b and saves the result in a. Increases the size of a when needed.
 */
void vector_vector_add_assignment(double_vector *a, double_vector *b);

/**
 * Calculates @p x * @p a and stores the result in a.
 */
void number_vector_mult_assignment(double x, double_vector *a);

/**
 * Sets @p a to (1- @p lambda)* @p a + @p lambda* @p b
 */
void vector_convex_assignment(double_vector *a, double_vector *b, double lambda );

/**
 * Scales @p a by @d
 */
void vector_scale_assignment(double_vector *a, double d);

/**
 * Test if @p a and @p b are equal.
 * @return 0 if a and b are equal, -1 if the sizes are different and the number of the first item that 
 *         is not equal + 1 in any other case.
 */
int double_vector_cmp(double_vector *a, double_vector *b);

/**
 * Compares @p a and @p b and allows a maximum deviation of @p delta
 */
int double_vector_cmp_delta(double_vector *a, double_vector *b, double delta );

#endif
