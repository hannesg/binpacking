/*
 * mixed_vector.h
 *
 *  Created on: Mar 27, 2011
 *      Author: hannes
 */

#ifndef MIXED_VECTOR_H_
#define MIXED_VECTOR_H_

#include "types.h"
#include "double_vector.h"
#include "uint_vector.h"

/**
 * Calculates the scalar product of @p a and @p b.
 */
double double_uint_vector_scalar_mult(double_vector *a, uint_vector *b);


#endif /* MIXED_VECTOR_H_ */
