/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

// Standard
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    result->array_height = height;

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

void uint_matrix_change_height(uint_matrix *matrix, unsigned int height)
{
    if(height > matrix->array_height) {
        if(height >= 1024) {
            matrix->array_height = (height / 1024 + 1) * height;
        }
        while(height > matrix->array_height) {
            matrix->array_height *= 2;
        }
        matrix->values = realloc(matrix->values, sizeof(unsigned int) * matrix->height * matrix->array_height);
    }
    matrix->height = height;
}

void uint_matrix_append_row(uint_matrix *matrix, uint_vector *vector)
{
    assert(vector->size == matrix->width);
    int row = matrix->height;
    uint_matrix_change_height(matrix, matrix->height + 1);
    memcpy(matrix->values + row * matrix->width, vector->values, matrix->width * sizeof(unsigned int));
}

unsigned int uint_matrix_ensure_row_existence(uint_matrix *matrix, uint_vector *row)
{
    assert(row->size == matrix->width);
    
    int rowNr;
    for(rowNr = 0; rowNr < matrix->height; ++rowNr) {
        int colNr;
        for(colNr = 0; colNr < matrix->height; ++colNr) {
            if(uint_matrix_elem(matrix, rowNr, colNr) != uint_vector_elem(row, colNr)) {
                break;
            }
        }
        if(colNr == matrix->height) {
            return rowNr;
        }
    }
    
    uint_matrix_append_row(matrix, row);
    return matrix->height - 1;
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

