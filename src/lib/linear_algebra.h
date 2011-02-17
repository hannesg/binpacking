/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "packing_list.h"

#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

// Vectors
typedef struct {
    unsigned int size;
    unsigned int * values;
} uint_vector;

typedef struct {
    unsigned int size;
    double * values;
} double_vector;

// Matrices
/**
 * A matrix of unsigned int values with height and width with
 * height * width elements. 
 * To get the element in row i and column j use 
 * A.values[i * A.width + j].
 */
typedef struct {
    unsigned int height;
    unsigned int width;
    unsigned int * values;
} uint_matrix;

/**
 * A matrix of double values with height and width with
 * height * width elements. 
 * To get the element in row i and column j use 
 * A.values[i * A.width + j].
 */
typedef struct {
    unsigned int height;
    unsigned int width;
    double * values;
} double_matrix;

double_vector *alloc_double_vector(unsigned int size);
void free_double_vector(double_vector *vector);

void fill_double_vector(double_vector *vector, double value);

double_matrix *alloc_double_matrix(unsigned int height, unsigned int width);
void free_double_matrix(double_matrix *matrix);

/**
 * Calculates x^T * A
 */
double_vector * vector_matrix_mult(double_vector *x, double_matrix *A);

#endif

