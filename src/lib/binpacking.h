/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#ifndef BINPACKING_H_
#define BINPACKING_H_

/** @file binpacking.h
 *  @brief Approximative Binpacking algorithm
 */

#include "packing_list.h"
#include "first_fit.h"
#include "linear_algebra.h"
#include <math.h>


packing_list * binpacking(double items[], double epsilon, unsigned int n);

/** @brief Sorts the given items and writes a list ( new_position => old_position ) into positions.
 *
 *  @param items the items
 *  @param n the number of items
 *  @param positions the positions
 *
 */
void track_sort_items(double items[], unsigned int n, unsigned int positions[]);

/** @brief Creates a positions list to be used with track_sort_items.
 *
 * @param n the number of items
 * @return a field of n entries filled with 0 to n-1
 *
 */
unsigned int *alloc_positions(unsigned int n);


/** @brief Exchanges every item number according to positions.
 *
 */
void renumber_packing_list(packing_list * list, item_number * positions);

/** @brief Creates a Matrix with all possible packings.
 *
 */
uint_matrix *matrix_from_items(double items[], unsigned int n, unsigned int limit);

#endif
