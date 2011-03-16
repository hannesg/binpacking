/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

// Standard
#include "stdio.h"

// Self
#include "print_double_array.h"

void print_double_array(double* array, int size)
{
    int i;
    for(i = 0; i < size; ++i) {
        printf("%lf\n", array[i]);
    }
}
