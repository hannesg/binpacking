/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include <time.h>

#include "CuTest.h"
#include "knapsack.h"
#include "uint_matrix.h"
#include "uint_vector.h"

void Test_knapsack_should_work(CuTest *ct){

    uint_vector *sizes = alloc_uint_vector(3);
    sizes->values[0] = 1;
    sizes->values[1] = 2;
    sizes->values[2] = 3;

    uint_vector *profits = alloc_uint_vector(3);
    profits->values[0] = 1;
    profits->values[1] = 10;
    profits->values[2] = 12;

    uint_vector *result = bound_knapsack(sizes, profits, 15, 3);

    print_uint_vector(result);

}

