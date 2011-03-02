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

void fill_double_vector(double_vector *vector, double value)
{
    int i;
    for(i = 0; i < vector->size; ++i) {
        vector->values[i] = value;
    }
}

void vector_vector_add_assignment(double_vector *a, double_vector *b)
{
    assert(a->size == b->size);

    int i;
    for(i = 0; i < a->size; ++i) {
        a->values[i] = a->values[i] + b->values[i];
    }
}

void number_vector_mult_assignment(double x, double_vector *a)
{
    int i;
    for(i = 0; i < a->size; ++i) {
        a->values[i] = x * a->values[i];
    }
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

void print_double_vector(double_vector *vector)
{
    int i;
    for(i = 0; i < vector->size; ++i) {
        printf("%lf\n", vector->values[i]);
    }
}

uint_matrix *alloc_uint_matrix(unsigned int height, unsigned int width)
{
    uint_matrix *result = (uint_matrix *) malloc(sizeof(uint_matrix));
    result->height = height;
    result->width = width;
    result->values = (unsigned int *) malloc(sizeof(unsigned int) * height * width);

    return result;
}

void free_uint_matrix(uint_matrix *matrix){
    free(matrix->values);
    free(matrix);
}

unsigned int uint_matrix_elem(uint_matrix *matrix, unsigned int row, unsigned int col){
    return matrix->values[ matrix->height*row + col ];
}

uint_vector * alloc_uint_vector(unsigned int size)
{
    uint_vector *result = (uint_vector *) malloc(sizeof(uint_vector));
    result->size = size;
    result->values = (unsigned int *) malloc(sizeof(unsigned int) * size);

    return result;
}

void free_uint_vector(uint_vector * vector)
{
    free(vector->values);
    free(vector);
}

void fill_uint_vector(uint_vector *vector, unsigned int value){
    unsigned int i;
    for(i = 0; i < vector->size; ++i) {
        vector->values[i] = value;
    }
}
