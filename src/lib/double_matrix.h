/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#ifndef DOUBLE_MATRIX_H
#define DOUBLE_MATRIX_H

#include "types.h"

/**
 * A matrix of double values with height and width with
 * height * width elements. 
 * To get the element in row i and column j use 
 * A.values[i * A.width + j].
 */
struct double_matrix_s {
    unsigned int height;
    unsigned int width;
    double * values;
};

/**
 * Allocate a @p height X @p width matrix of double values.
 */
double_matrix *alloc_double_matrix(unsigned int height, unsigned int width);

/**
 * Free the double matrix @p matrix.
 */
void free_double_matrix(double_matrix *matrix);

/**
 * Print a formatted output of the matrix values.
 */
void print_double_matrix(double_matrix *matrix);

/**
 * Calculates x^T * A
 */
double_vector * vector_matrix_mult(double_vector *x, double_matrix *A);

/**
 * Calculates x^T * A^T
 */
double_vector *vector_transposed_matrix_mult(double_vector *x, double_matrix *A);

/**
 * Calculates A * x
 */
double_vector *matrix_vector_mult(double_matrix *A, double_vector *x);

/**
 * Calculates A^T * x
 */
double_vector *transposed_matrix_vector_mult(double_matrix *A, double_vector *x);

#endif
