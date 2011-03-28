/*
 * knapsack.h
 *
 *  Created on: Mar 17, 2011
 *      Author: hannes
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

/** @file knapsack.h
 *  @brief Exact and Approximative Knapsack algorithm
 */


#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "uint_vector.h"
#include "uint_matrix.h"
#include "double_vector.h"

/**
 * Calculates a knapsack configuration S such that
 *
 * @p sizes * S <= @p B
 *
 * @p profits * S = max( profits * U | @p sizes * S <= @p B )
 *
 * @param sizes the sizes of the items
 * @param profits the profits of the items
 * @param B the knapsack size
 * @param limit a limit for frequency of each item
 *
 * @returns the optimal knapsack configuration S
 */
uint_vector *bound_knapsack( double_vector *sizes,
                             uint_vector *profits,
                             double B,
                             unsigned int limit);


/**
 * Calculates a knapsack configuration S such that
 *
 * @p sizes * S <= @p B
 *
 * @p profits * S >= (1-precision) * max( profits * U | @p sizes * S <= @p B )
 *
 * @param sizes the sizes of the items
 * @param profits the profits of the items
 * @param B the knapsack size
 * @param limit a limit for frequency of each item
 * @param precision the desired precision
 *
 * @returns the nearly optimal knapsack configuration S
 */
uint_vector *approximate_bound_knapsack( double_vector *sizes,
                             double_vector *profits,
                             double B,
                             unsigned int limit,
                             double precision);

/**
 *
 */
double_vector * approximate_bound_knapsack_block_solver(
                             uint_matrix *A,
                             double_vector *sizes,
                             double_vector *profits,
                             double B,
                             unsigned int limit,
                             double precision);


#endif /* KNAPSACK_H_ */
