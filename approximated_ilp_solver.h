/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "vector.h"

/**
 * Solves the ILP @p A * x = @p b with the target function sum(A_i).
 * The quality of the result is (1 - @p precision) * OPT.
 * 
 * @return The approximated solution.
 */
int_vector * approximated_ilp_solver(uint_matrix * A,
                                     uint_vector * b,
                                     double precision);
