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

// Alloc
/**
 * Allocate a vector of @p size doubles.
 */
double_vector *alloc_double_vector(unsigned int size);

/**
 * Allocate a @p height X @p width matrix of double values.
 */
double_matrix *alloc_double_matrix(unsigned int height, unsigned int width);

/**
 * Allocate an unsigned integer vector with the size @p size.
 */
uint_vector *alloc_uint_vector(unsigned int size);

/**
 * Allocate a @p height X @p width matrix of unsigned int values.
 */
uint_matrix *alloc_uint_matrix(unsigned int height, unsigned int width);

// Free
/**
 * Free the double vector @p vector.
 */
void free_double_vector(double_vector *vector);

/**
 * Free the double matrix @p matrix.
 */
void free_double_matrix(double_matrix *matrix);

/**
 * Free the unsigned int vector @p vector.
 */
void free_uint_vector(uint_vector *vector);

/**
 * Free the unsigned int matrix @p matrix.
 */
void free_uint_matrix(uint_matrix *matrix);

// Initialization
/** 
 * Fill the double vector @p vector with the value @p value.
 */
void fill_double_vector(double_vector *vector, double value);

/**
 * Fill the unsigned integer vector @p vector with the value @p value.
 */
void fill_uint_vector(uint_vector *vector, unsigned int value);

// Assignment calculations (calculations that save the result in one of the 
// input variables.
/**
 * Calculates a + b and saves the result in a.
 */
void vector_vector_add_assignment(double_vector *a, double_vector *b);

/**
 * Calculates @p x * @p a and stores the result in a.
 */
void number_vector_mult_assignment(double x, double_vector *a);

// Comparison
/**
 * Test if @p a and @p b are equal.
 * @return 0 if a and b are equal, -1 if the sizes are different and the number of the first item that 
 *         is not equal + 1 in any other case.
 */
int double_vector_cmp(double_vector *a, double_vector *b);

// Output
/**
 * Print a formatted output of the vector values.
 */
void print_double_vector(double_vector *vector);

/**
 * Print a formatted output of the matrix values.
 */
void print_double_matrix(double_matrix *matrix);

/**
 * Print a formatted output of the matrix values.
 */
void print_uint_matrix(uint_matrix *matrix);

// Others
/**
 * Returns the element in row @p row and column @p col of the matrix @p matrix.
 */
inline unsigned int uint_matrix_elem(uint_matrix *matrix, unsigned int row, unsigned int col);

// Normal calculations.
/**
 * Calculates x^T * A
 */
double_vector * vector_matrix_mult(double_vector *x, double_matrix *A);

/**
 * Calculates A * x^T
 */
double_vector *matrix_vector_mult(double_matrix *A, double_vector *x);

/**
 * Calculates the minimum of all items in the vector @p x
 */
double vector_min(double_vector *x);

/**
 * Calculates the scalar product of @p a and @p b.
 */
double vector_scalar_mult(double_vector *a, double_vector *b);

/**
 * Divides every row of the matrix @p A by the corresponding row in the vector @p b.
 */
double_matrix *uint_matrix_vector_division(uint_matrix *A, uint_vector *b);

/**
 * Sets @p a to (1- @p lambda)* @p a + @p lambda* @p b
 */
void vector_convex_assignment(double_vector *a, double_vector *b, double lambda );

/**
 * Scales @p a by @d
 */
void vector_scale_assignment(double_vector *a, double d);

/**
 * Compares @p a and @p b and allows a maximum deviation of @p delta
 */
int double_vector_cmp_delta(double_vector *a, double_vector *b, double delta );

#endif

