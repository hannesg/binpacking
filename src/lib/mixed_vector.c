/*
 * mixed_vector.c
 *
 *  Created on: Mar 27, 2011
 *      Author: hannes
 */

#include "mixed_vector.h"

double double_uint_vector_scalar_mult(double_vector *a, uint_vector *b){
    assert( a->size == b->size );
    double result = 0;
    unsigned int i = 0;
    for( i=0; i < a->size ; i++ ){
        result += a->values[i]*b->values[i];
    }
    return result;
}
