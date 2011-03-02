/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Library
#include "approximate_block_solver.h"

// Self
#include "approximate_max_min_resource_sharing.h"

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
        // TODO: Add the improving part.
        break;
    }
    
    free_double_vector(p);
    return x;
}
