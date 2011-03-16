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
#include "double_matrix.h"
#include "uint_vector.h"

// Self
#include "uint_matrix.h"

uint_matrix *alloc_uint_matrix(unsigned int height, unsigned int width)
{
    uint_matrix *result = (uint_matrix *) malloc(sizeof(uint_matrix));
    result->height = height;
    result->width = width;
    result->values = (unsigned int *) malloc(sizeof(unsigned int) * height * width);

    return result;
}

void free_uint_matrix(uint_matrix *matrix) {
    if(matrix == NULL) {
        return;
    }
    free(matrix->values);
    free(matrix);
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

unsigned int uint_matrix_elem(uint_matrix *matrix, unsigned int row, unsigned int col){
    return matrix->values[ matrix->width*row + col ];
}

uint_vector *uint_matrix_row(uint_matrix *matrix, unsigned int row)
{
    uint_vector *result = alloc_uint_vector(matrix->width);
    int col;
    for(col = 0; col < matrix->width; ++col) {
        result->values[col] = matrix->values[matrix->width * row + col];
    }
    
    return result;
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

