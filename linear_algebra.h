/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#ifndef LINEAR_ALGEBRA_H_
#define LINEAR_ALGEBRA_H_

#include "packing_list.h"

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

#endif
