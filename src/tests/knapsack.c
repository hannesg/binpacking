/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include <time.h>

#include "CuTest.h"
#include "knapsack.h"
#include "uint_matrix.h"
#include "uint_vector.h"

void Test_knapsack_should_work_on_small_instances(CuTest *tc){

    uint_vector *sizes = alloc_uint_vector(3);
    sizes->values[0] = 2;
    sizes->values[1] = 3;
    sizes->values[2] = 4;

    uint_vector *profits = alloc_uint_vector(3);
    profits->values[0] = 1;
    profits->values[1] = 3;
    profits->values[2] = 4;

    uint_vector *result;

    result = bound_knapsack(sizes, profits, 10, 2);

    CuAssertIntEquals(tc, 10, uint_vector_scalar_mult(result, profits));

    free(result);

    result = bound_knapsack(sizes, profits, 11, 2);

    CuAssertIntEquals(tc, 11, uint_vector_scalar_mult(result, profits));

    free(result);

    result = bound_knapsack(sizes, profits, 12, 2);

    CuAssertIntEquals(tc, 11, uint_vector_scalar_mult(result, profits));

    free(result);

    result = bound_knapsack(sizes, profits, 13, 2);

    CuAssertIntEquals(tc, 12, uint_vector_scalar_mult(result, profits));

    free(result);

    result = bound_knapsack(sizes, profits, 14, 2);

    CuAssertIntEquals(tc, 14, uint_vector_scalar_mult(result, profits));

    free(result);
}

void Test_knapsack_should_work_on_medium_instances(CuTest *tc){

    uint_vector *sizes = alloc_uint_vector(10);
    sizes->values[0] = 2;
    sizes->values[1] = 3;
    sizes->values[2] = 4;
    sizes->values[3] = 9;
    sizes->values[4] = 10;
    sizes->values[5] = 15;
    sizes->values[6] = 19;
    sizes->values[7] = 50;
    sizes->values[8] = 59;
    sizes->values[9] = 102;
    /*    sizes->values[10] = 32;
    sizes->values[11] = 12;
    sizes->values[12] = 22;
    sizes->values[13] = 3;
    sizes->values[14] = 41;
    sizes->values[15] = 22;
    sizes->values[16] = 34;
    sizes->values[17] = 42;
    sizes->values[18] = 229;
    sizes->values[19] = 31;*/

    uint_vector *profits = alloc_uint_vector(10);
    profits->values[0] = 1;
    profits->values[1] = 3;
    profits->values[2] = 4;
    profits->values[3] = 10;
    profits->values[4] = 20;
    profits->values[5] = 14;
    profits->values[6] = 20;
    profits->values[7] = 66;
    profits->values[8] = 61;
    profits->values[9] = 125;
/*    profits->values[10] = 40;
    profits->values[11] = 13;
    profits->values[12] = 22;
    profits->values[13] = 4;
    profits->values[14] = 20;
    profits->values[15] = 1;
    profits->values[16] = 32;
    profits->values[17] = 41;
    profits->values[18] = 240;
    profits->values[19] = 31;*/

    uint_vector *result;

    result = bound_knapsack(sizes, profits, 103, 2);

    CuAssertIntEquals(tc, 140, uint_vector_scalar_mult(result, profits));

    free(result);

}

