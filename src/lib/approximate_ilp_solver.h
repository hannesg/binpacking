/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "linear_algebra.h"

/**
 * Solves the ILP @p A ^T * x = @p b with the target function sum(A_i).
 * The quality of the result is (1 - @p precision) * OPT.
 * 
 * @return The approximated solution.
 */
int_vector * approximate_ilp_solver(uint_matrix * A,
                                     uint_vector * b,
                                     double precision);
