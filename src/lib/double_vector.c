/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

// Standard
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

// Project
#include "uint_vector.h"

// Self
#include "double_vector.h"

double_vector * alloc_double_vector(unsigned int size)
{
    double_vector *result = (double_vector *) malloc(sizeof(double_vector));
    result->size = size;
    result->values = (double *) malloc(sizeof(double) * size);
    
    return result;
}
    
void free_double_vector(double_vector * vector)
{
    if(vector == NULL) {
        return;
    }
    free(vector->values);
    free(vector);
}

void print_double_vector(double_vector *vector)
{
    int i;
    for(i = 0; i < vector->size; ++i) {
        printf("%lf\n", vector->values[i]);
    }
}

void fill_double_vector(double_vector *vector, double value)
{
    int i;
    for(i = 0; i < vector->size; ++i) {
        vector->values[i] = value;
    }
}

void sort_double_array_order(double *array, unsigned int *order, unsigned int size) {
    unsigned int left = 1, right = size - 1, temp;
    
    if(size <= 1) {
        return;
    }
    
    while(left < right && array[order[left]] >= array[order[0]]) {
        left++;
    }
    while(array[order[right]] < array[order[0]]) {
        right--;
    }
    while(left < right) {
        // exchange the order
        temp = order[left];
        order[left] = order[right];
        order[right] = temp;
        
        while(left < right && array[order[left]] >= array[order[0]]) {
            left++;
        }
        while(array[order[right]] < array[order[0]]) {
            right--;
        }
    }
    
    // Putting the pivot element in the right position
    temp = order[0];
    order[0] = order[right];
    order[right] = temp;
    
    sort_double_array_order(array, order, right);
    sort_double_array_order(array, order + right + 1, size - right - 1);
}

uint_vector *double_vector_order(double_vector *vector) {
    uint_vector *result = alloc_uint_vector(vector->size);
    
    // Initial fill
    int i;
    for(i = 0; i < vector->size; ++i) {
        result->values[i] = i;
    }
    
    // Sorting
    sort_double_array_order(vector->values, result->values, vector->size);
    
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

double vector_sum(double_vector *x)
{
    double sum = 0.0;
    int i;
    for(i = 0; i < x->size; ++i) {
        sum += x->values[i];
    }
    
    return sum;
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

void vector_vector_add_assignment(double_vector *a, double_vector *b)
{
    unsigned int i;
    if(a->size < b->size){
        // rescale a
        a->values = realloc(a->values, b->size * sizeof(double));
        for( i = a->size; i < b->size; i++ ){
            a->values[i] = 0.0;
        }
        a->size = b->size;
    }
    for(i = 0; i < b->size; ++i) {
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

void vector_number_div_assignment(double_vector *a, double x)
{
    if(x == 0) {
        return;
    }
    int i;
    for(i = 0; i < a->size; ++i) {
        a->values[i] = a->values[i] / x;
    }
}

void vector_convex_assignment(double_vector *a, double_vector *b, double lambda ){
    double one_minus_lambda = 1 - lambda;
    unsigned int i;
    for(i = 0; i < a->size; ++i) {
        a->values[i] = (one_minus_lambda * a->values[i]) + (lambda * b->values[i]);
    }
}

void vector_scale_assignment(double_vector *a, double d){
    unsigned int i;
    for(i = 0; i < a->size; ++i) {
        a->values[i] *= d;
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
