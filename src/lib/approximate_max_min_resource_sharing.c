/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Standard library
#include <math.h>

// Library
#include "approximate_block_solver.h"

// Self
#include "approximate_max_min_resource_sharing.h"

double calculate_optimum_condition(double_vector *b, double theta, double t)
{
    double result = 0;
    
    int i;
    for(i = 0; i < b->size; ++i) {
        result += theta / (b->values[i] - theta);
    }
    result *= t/((double) b->size);
}

double find_optimum(double_matrix *A, double_vector *x, double t)
{
    double_vector *function_solution = matrix_vector_mult(A, x);
    
    double minimum = 0;
    double maximum = vector_min(function_solution);
    
    double medium = 0.5 * (minimum + maximum);
    double optimum_condition = calculate_optimum_condition(function_solution, medium, t);
    while(fabs(optimum_condition - 1) > t && minimum < maximum) {
        if(optimum_condition < 1) {
            minimum = medium;
        } else {
            maximum = medium;
        }
        
        double medium = 0.5 * (minimum + maximum);
        double optimum_condition = calculate_optimum_condition(function_solution, medium, t);
    }
    
    return medium;
}

double_vector *approximate_max_min_resource_sharing(double_matrix *A,
                                                    unsigned int limit,
                                                    double precision)
{
    // The vector to contain the solution.
    double_vector *x = alloc_double_vector(A->width);
    fill_double_vector(x, 0.0);
    
    // A vector needed to compute the starting solution.
    double_vector *p = alloc_double_vector(A->height);
    fill_double_vector(p, 0.0);
    
    // Compute the starting solution.
    int m;
    for(m = 0; m < A->height; m++) {
        p->values[m] = 1.0;
        double_vector *block_solution = approximate_block_solver(A, p, limit, 0.5);
        vector_vector_add_assignment(x, block_solution);
        p->values[m] = 0.0;
    }
    free_double_vector(p); p = NULL;
    number_vector_mult_assignment(1.0/((double) A->height), x);
    
    double approximate_block_solver_precision = precision / 6;
    while(1) {
        double theta = find_optimum(A, x, approximate_block_solver_precision);
        
        // TODO: Add the improving part.
        
        
        break;
    }
    
    free_double_vector(p);
    return x;
}
