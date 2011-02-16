/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "packing_list.h"

typedef struct {
    unsigned int size;
    unsigned int * values;
} uint_vector;

typedef struct {
    unsigned int height;
    unsigned int width;
    int * values;
} uint_matrix;

typedef struct {
    unsigned int size;
    double * values;
} double_vector;


