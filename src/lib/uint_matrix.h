/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#ifndef UINT_MATRIX_H
#define UINT_MATRIX_H

#include "types.h"
#include "double_vector.h"

/**
 * A matrix of unsigned int values with height and width with
 * height * width elements. 
 * To get the element in row i and column j use 
 * A.values[i * A.width + j].
 */
struct uint_matrix_s {
    unsigned int height;
    unsigned int width;
    unsigned int *values;
    
    unsigned int array_height;
};


/**
 * Allocate a @p height X @p width matrix of unsigned int values.
 */
uint_matrix *alloc_uint_matrix(unsigned int height, unsigned int width);

/**
 * Free the unsigned int matrix @p matrix.
 */
void free_uint_matrix(uint_matrix *matrix);

/**
 * Print a formatted output of the matrix values.
 */
void print_uint_matrix(uint_matrix *matrix);

/**
 * Change the height of the matrix to @p height.
 */
void uint_matrix_change_height(uint_matrix *matrix, unsigned int height);

/**
 * Append the given vector @p vector to the given matrix @p matrix.
 */
void uint_matrix_append_row(uint_matrix *matrix, uint_vector *vector);

/**
 * Ensure the existence of the row @p row in the matrix @p matrix.
 * If it is not existent the row will be appended to the matrix.
 * @return The number of the row.
 */
unsigned int uint_matrix_ensure_row_existence(uint_matrix *matrix, uint_vector *row);

/**
 * Returns the element in row @p row and column @p col of the matrix @p matrix.
 */
inline unsigned int uint_matrix_elem(uint_matrix *matrix, unsigned int row, unsigned int col);

inline uint_vector *uint_matrix_row(uint_matrix *matrix, unsigned int row);

/**
 * Divides every row of the matrix @p A by the corresponding row in the vector @p b.
 */
double_matrix *uint_matrix_vector_division(uint_matrix *A, uint_vector *b);

/**
 * Divides every column of the matrix @p A by the corresponding row in the vector @p b.
 */
double_matrix *uint_transposed_matrix_vector_division(uint_matrix *A, uint_vector *b);


double_vector *uint_transposed_matrix_vector_mult(uint_matrix *A, double_vector *x);

#endif
