// Standard library
#include <assert.h>
#include <math.h>

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

double_vector *vector_transposed_matrix_mult(double_vector *x, double_matrix *A)
{
    assert(x->size == A->width);
    
    double_vector *result = alloc_double_vector(A->height);
    
    int row;
    for(row = 0; row < A->height; ++row) {
        double row_sum = 0.0;
        
        int column;
        for(column = 0; column < A->width; ++column) {
            row_sum += x->values[column] * A->values[row * A->width + column];
        }
        
        result->values[row] = row_sum;
    }
    
    return result;
}

double_vector *matrix_vector_mult(double_matrix *A, double_vector *x)
{
    assert(x->size == A->width);
    
    double_vector *result = alloc_double_vector(A->height);
    
    int row;
    for(row = 0; row < A->height; ++row) {
        double row_sum = 0;
        int column;
        
        for(column = 0; column < A->width; ++column) {
            row_sum += A->values[row * A->width + column] * x->values[column];
        }
        result->values[row] = row_sum;
    }
    
    return result;
}

double_vector *transposed_matrix_vector_mult(double_matrix *A, double_vector *x)
{
    assert(x->size == A->height);
    
    double_vector *result = alloc_double_vector(A->width);
    fill_double_vector(result, 0.0);
    
    int row;
    for(row = 0; row < A->height; ++row) {
        int column;
        
        for(column = 0; column < A->width; ++column) {
            result->values[column] += A->values[row * A->width + column] * x->values[row];
        }
    }
    
    return result;
}

double vector_min(double_vector *x)
{
    assert(x->size > 0);
    double result = x->values[0];
    
    int i;
    for(i = 1; i < x->size; ++i) {
        if(x->values[i] < result) {
            result = x->values[i];
        }
    }
    
    return result;
}

double vector_scalar_mult(double_vector *a, double_vector *b)
{
    assert(a->size == b->size);
    
    double result = 0.0;
    int i;
    for(i = 0; i < a->size; ++i) {
        result += a->values[i] * b->values[i];
    }
    
    return result;
}

void vector_scale_assignment(double_vector *a, double d){
    unsigned int i;
    for(i = 0; i < a->size; ++i) {
        a->values[i] *= d;
    }
}

void vector_convex_assignment(double_vector *a, double_vector *b, double lambda ){
    double one_minus_lambda = 1 - lambda;
    unsigned int i;
    for(i = 0; i < a->size; ++i) {
        a->values[i] = (one_minus_lambda * a->values[i]) + (lambda * b->values[i]);
    }
}


int double_vector_cmp(double_vector *a, double_vector *b)
{
    if(a->size != b->size) {
        return -1;
    }
    
    int i;
    for(i = 0; i < a->size; i++) {
        if(a->values[i] != b->values[i]) {
            return i+1;
        }
    }
    
    return 0;
}

int double_vector_cmp_delta(double_vector *a, double_vector *b, double delta )
{
    if(a->size != b->size) {
        return -1;
    }

    int i;
    for(i = 0; i < a->size; i++) {
        if( fabs(a->values[i] - b->values[i]) > delta ) {
            return i+1;
        }
    }

    return 0;
}

void print_double_vector(double_vector *vector)
{
    int i;
    for(i = 0; i < vector->size; ++i) {
        printf("%lf\n", vector->values[i]);
    }
}

void print_double_matrix(double_matrix *matrix)
{
    int row;
    for(row = 0; row < matrix->height; ++row) {
        int column;
        for(column = 0; column < matrix->width; ++column) {
            printf("%4.2lf ", matrix->values[row * matrix->width + column]);
        }
        printf("\n");
    }
}

void print_uint_matrix(uint_matrix *matrix)
{
    int row;
    for(row = 0; row < matrix->height; ++row) {
        int column;
        for(column = 0; column < matrix->width; ++column) {
            printf("%4i ", matrix->values[row * matrix->width + column]);
        }
        printf("\n");
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

double_matrix *uint_matrix_vector_division(uint_matrix *A, uint_vector *b)
{
    assert(A->height == b->size);

    double_matrix *result = alloc_double_matrix(A->height, A->width);
    
    int row;
    for(row = 0; row < A->height; ++row) {
        int column;
        
        for(column = 0; column < A->width; ++column) {
            result->values[row * A->width + column] = ((double) A->values[row * A->width + column]) / 
                                                      ((double) b->values[row]);
        }
    }
    
    return result;
}

double_matrix *uint_transposed_matrix_vector_division(uint_matrix *A, uint_vector *b)
{
    assert(A->width == b->size);
    
    double_matrix *result = alloc_double_matrix(A->height, A->width);
    
    int column;
    for(column = 0; column < A->width; ++column) {
        int row;
        
        for(row = 0; row < A->height; ++row) {
            result->values[row * A->width + column] = ((double) A->values[row * A->width + column]) / 
                                                      ((double) b->values[column]);
        }
    }
    
    return result;
}
