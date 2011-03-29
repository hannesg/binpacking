/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Standard
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Project
#include "approximate_max_min_resource_sharing.h"
#include "double_vector.h"
#include "double_matrix.h"
#include "uint_matrix.h"

// Self
#include "approximate_lp_solver.h"

double_vector *approximate_lp_solver(uint_matrix *A,
                                     uint_vector *b,
                                     double precision,
                                     unsigned int min,
                                     unsigned int max)
{
    int minimum = min;     // area
    int maximum = max; // 2 * area + 1
    
    double_matrix *matrix = uint_transposed_matrix_vector_division(A, b);
    max_min_resource_sharing_solution *end_solution = NULL;
    int medium;
    do {
        medium =  (minimum + maximum)/2; // This does not fail because limit is small.
        max_min_resource_sharing_solution *solution
            = approximate_max_min_resource_sharing(matrix,
                                                   medium,
                                                   precision);
            
        if(solution->function_solution_min >= 1.0) {
            maximum = medium;
            free_max_min_resource_sharing_solution(end_solution);
            end_solution = solution;
        } else {
            minimum = medium + 1;
            free_max_min_resource_sharing_solution(solution);
        }
    } while(minimum < maximum);
    
    free_double_matrix(matrix);

    if(end_solution == NULL) {
        // We did not find an solution.
        return NULL;
    }
    else {
        // We only need the solution_vector, the values are unneded for us.
        free_double_vector(end_solution->function_solution);
        double_vector *solution_vector = end_solution->vector;
        free(end_solution);
        return solution_vector;
    }
}

double_vector *approximate_rbp_lp_solver(double_vector *items,
                                         unsigned int k,
                                     uint_matrix *A,
                                     double precision)
{
    double area = vector_sum(items) * k;
    int minimum = ceil(area);
    int maximum = ceil(2 * area + 1);

    uint_matrix *matrix = NULL;
    max_min_resource_sharing_solution *end_solution = NULL;
    int medium;
    do {
        medium =  (minimum + maximum)/2; // This does not fail because limit is small.
        matrix = alloc_uint_matrix(0, items->size);
        max_min_resource_sharing_solution *solution
            = approximate_rbp_lp_max_min_resource_sharing(
                                                   items,
                                                   matrix,
                                                   medium,
                                                   precision);

        if(solution->function_solution_min >= 1.0) {
            maximum = medium;
            free_max_min_resource_sharing_solution(end_solution);
            end_solution = solution;
        } else {
            minimum = medium + 1;
            free_max_min_resource_sharing_solution(solution);
            free_uint_matrix(matrix);
        }
    } while(minimum < maximum);

    if(end_solution == NULL) {
        // We did not find an solution.
        return NULL;
    }
    else {
        // We only need the solution_vector, the values are unneded for us.
        free_double_vector(end_solution->function_solution);
        double_vector *solution_vector = end_solution->vector;
        free(end_solution);
        A->values = matrix->values;
        A->width = matrix->width;
        A->height = matrix->height;
        A->array_height = matrix->array_height;
        free(matrix);
        return solution_vector;
    }
}
