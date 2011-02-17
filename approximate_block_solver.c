/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Self
#include "approximate_block_solver.h"

double_vector *approximate_block_solver(double_matrix *A,
                                        double_vector *p,
                                        uint *limit,
                                        double precision)
{
    double_vector *profits = vector_matrix_mult(p, A);
    
    unsigned int i;
    double largest_value = profits->values[0];
    unsigned int largest_index = 0;
    for(i = 1; i < profits->size; ++i) {
        if(profit->values[i] > largest_value) {
            largest_value = profit->values[i];
            largest_index = i;
        }
    }

    double_vector *result = alloc_double_vector(profits->size);
    fill_double_vector(result, 0.0);
    result->values[largest_index] = limit;
    return result;
}
