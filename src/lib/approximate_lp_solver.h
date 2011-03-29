/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "types.h"

/**
 * Solves the LP @p A ^T * x = @p b with the target function sum(A_i).
 * The quality of the result is (1 - @p precision) * OPT.
 * 
 * @return The approximated solution.
 */
double_vector *approximate_lp_solver(uint_matrix *A,
                                     uint_vector *b,
                                     double precision,
                                     unsigned int min,
                                     unsigned int max);

/**
 * Solves the LP(RBP) defined by the @p items and the @p limit.
 * The matrix @p A contains the used subset of the full LP matrix
 * The quality of the result is (1 - @p precision) * OPT.
 *
 * @return The approximated solution.
 */
double_vector *approximate_rbp_lp_solver(double_vector *items,
                                     uint_matrix *A,
                                     double precision);
