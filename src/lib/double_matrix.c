/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

// Standard
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Project
#include "double_vector.h"

// Self
#include "double_matrix.h"

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
    if(matrix == NULL) {
        return;
    }
    free(matrix->values);
    free(matrix);
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
        if( x->values[row] == 0.0 ){
            continue ;
        }
        int column;
        for(column = 0; column < A->width; ++column) {
            result->values[column] += A->values[row * A->width + column] * x->values[row];
        }
    }
    
    return result;
}
