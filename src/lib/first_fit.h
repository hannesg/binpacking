/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#ifndef FIRST_FIT_H_
#define FIRST_FIT_H_

#include "packing_list.h"

/** @file first_fit.h
 *  @brief First Fit algorithm
 */

/**
 * Packs all given item using the First Fit method
 *
 * @param items the items to pack
 * @param n the number of items
 * @return a packing list which contains all given items
 *
 */
packing_list * first_fit(double items[], unsigned int n);

/**
 * Packs one item in a packing list using the First Fit method
 *
 * @param items the items to pack
 * @param n the number of items
 * @param item the item to pack
 * @param result the packing list which will be modified
 *
 */
void first_fit_step(double items[], unsigned int n, item_number item,packing_list * result);

#endif
