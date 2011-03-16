/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Project
#include "types.h"

typedef struct {
    double_vector *vector;
    double_vector *function_solution;
    double function_solution_min;
} max_min_resource_sharing_solution;

void free_max_min_resource_sharing_solution(max_min_resource_sharing_solution *solution);

/**
 * @brief An approximate solver for the max min resource sharing problem.
 * Find the maximum lambda out of {lambda | it exists an x in B: for all i: (A^T * x)_i >= lambda}
 * with B = {x | sum x_i = limit}.
 * 
 * @return The approximated solution.
 */
max_min_resource_sharing_solution *approximate_max_min_resource_sharing(double_matrix *A,
                                                                        unsigned int limit,
                                                                        double precision);
