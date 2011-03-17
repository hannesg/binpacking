/*
 * knapsack.h
 *
 *  Created on: Mar 17, 2011
 *      Author: hannes
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#include "uint_vector.h"

uint_vector *bound_knapsack( uint_vector *sizes,
                             uint_vector *profits,
                             unsigned int B,
                             unsigned int limit);


#endif /* KNAPSACK_H_ */
