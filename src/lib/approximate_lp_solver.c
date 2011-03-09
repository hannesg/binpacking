/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Standard
#include <math.h>
#include <stdio.h>

// Project
#include "approximate_max_min_resource_sharing.h"

// Self
#include "approximate_lp_solver.h"

double_vector *approximate_lp_solver(uint_matrix *A,
                                     uint_vector *b,
                                     double precision,
                                     unsigned int limit)
{
    int minimum = 0;
    int maximum = limit;
    
    double_matrix *matrix = uint_matrix_vector_division(A, b);
    int medium;
    do {
        printf("Minimum: %i, maximum: %i\n", minimum, maximum);
        medium =  (minimum + maximum)/2; // This does not fail because limit is small.
        printf("Medium: %i\n", medium);
        max_min_resource_sharing_solution *solution
            = approximate_max_min_resource_sharing(matrix,
                                                   medium,
                                                   precision);
            
        if(solution->function_solution_min >= 1.0) {
            maximum = medium;
        } else {
            minimum = medium + 1;
        }
        
        free_max_min_resource_sharing_solution(solution);
    } while(minimum < maximum);
    
    max_min_resource_sharing_solution *end_solution
        = approximate_max_min_resource_sharing(matrix,
                                               maximum,
                                               precision);
    free_double_vector(end_solution->function_solution);
    free(end_solution);
    return end_solution->vector;
}
