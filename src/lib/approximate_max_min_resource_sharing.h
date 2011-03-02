/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "linear_algebra.h"

/**
 * @brief An approximate solver for the max min resource sharing problem.
 * 
 * @return The approximated solution.
 */
double_vector *approximate_max_min_resource_sharing(double_matrix *A,
                                                    unsigned int limit,
                                                    double precision);
