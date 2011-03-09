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
        medium = (minimum + maximum)/2; // This does not fail becaus limit is small.
        double_vector *resource_sharing_solution
            = approximate_max_min_resource_sharing(A,
                                                   medium,
                                                   precision);
        
}
