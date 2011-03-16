/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

// Standard
#include "stdio.h"

// Self
#include "print_uint_array.h"

void print_uint_array(unsigned int* array, int size)
{
    int i;
    for(i = 0; i < size; ++i) {
        printf("%u\n", array[i]);
    }
}

