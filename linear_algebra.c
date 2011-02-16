// Standard library
#include <assert.h>

// Self
#include "linear_algebra.h"

double_vector * alloc_double_vector(unsigned int size)
{
    double_vector *result = (double_vector *) malloc(sizeof(double_vector));
    result->size = size;
    result->values = (double *) malloc(sizeof(double) * size);
    
    return result;
}
    
void free_double_vector(double_vector * vector)
{
    free(vector->values);
    free(vector);
}

double_matrix *alloc_double_matrix(unsigned int height, unsigned int width)
{
    double_matrix *result = (double_matrix *) malloc(sizeof(double_matrix));
    result->height = height;
    result->width = width;
    result->values = (double *) malloc(sizeof(double) * height * width);
    
    return result;
}

void free_double_matrix(double_matrix *matrix)
{
    free(matrix->values);
    free(matrix);
}

double_vector *vector_matrix_mult(double_vector *x, double_matrix *A)
{
    assert(x->size == A->height);
    
    double_vector *result = alloc_double_vector(A->width);
    
    int column;
    for(column = 0; column < A->width; ++column) {
        double column_sum = 0;
        int row;
        for(row = 0; row < A->height; ++row) {
            column_sum += x->values[row] * A->values[row * A->width + column];
        }
        result->values[column] = column_sum;
    }
    
    return result;
}
