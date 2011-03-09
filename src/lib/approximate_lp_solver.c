/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "approximate_lp_solver.h"

double_vector *approximate_lp_solver(uint_matrix *A,
                                     uint_vector *b,
                                     double precision,
                                     unsigned int limit)
{
    int minimum = 0;
    int maximum = limit;
    int medium;
    do {
        medium = floor((minimum + maximum)/2); // This does not fail because limit is small.
        max_min_resource_sharing_solution *solution
            = approximate_max_min_resource_sharing(A,
                                                   medium,
                                                   precision);
            
        if(solution->function_solution_minimum >= 1.0) {
            maximum = medium;
        } else {
            minimum = medium + 1;
        }
        
        free_max_min_resource_sharing_solution(solution);
    } while(minimum < maximum);
    
    max_min_resource_sharing_solution *end_solution
        = approximate_max_min_resource_sharing(A,
                                               maximum,
                                               precision);
    free_double_vector(end_solution->function_solution);
    free(end_solution);
    return end_solution->vector;
}
