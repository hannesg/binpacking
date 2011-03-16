/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Project
#include "types.h"

/**
 * @brief An approximated block solver for linear functions.
 * 
 * Calculates an (1 - @p precisison) approximated solution for the problem
 * find x' in B with:
 * p^T * A^T * x' = max{p^T * A^T * x | x in B}
 * B = {x in R^(A.height) | sum(x_i) = @param limit, x_i >= 0}
 * 
 * @return The approximated solution.
 */
double_vector *approximate_block_solver(double_matrix *A,
                                        double_vector *p,
                                        unsigned int limit,
                                        double precision);
