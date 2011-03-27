/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include <time.h>

#include "CuTest.h"
#include "knapsack.h"
#include "uint_matrix.h"
#include "uint_vector.h"
#include "mixed_vector.h"

void Test_knapsack_should_work_on_small_instances(CuTest *tc){

    double_vector *sizes = alloc_double_vector(3);
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

    free_uint_vector(result);

    result = bound_knapsack(sizes, profits, 11, 2);

    CuAssertIntEquals(tc, 11, uint_vector_scalar_mult(result, profits));

    free_uint_vector(result);

    result = bound_knapsack(sizes, profits, 12, 2);

    CuAssertIntEquals(tc, 11, uint_vector_scalar_mult(result, profits));

    free_uint_vector(result);

    result = bound_knapsack(sizes, profits, 13, 2);

    CuAssertIntEquals(tc, 12, uint_vector_scalar_mult(result, profits));

    free_uint_vector(result);

    result = bound_knapsack(sizes, profits, 14, 2);

    CuAssertIntEquals(tc, 14, uint_vector_scalar_mult(result, profits));

    free_uint_vector(result);
    free_uint_vector(profits);
    free_double_vector(sizes);
}

void Test_knapsack_should_work_on_medium_instances(CuTest *tc){

    double_vector *sizes = alloc_double_vector(20);
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
    sizes->values[10] = 323;
    sizes->values[11] = 123;
    sizes->values[12] = 223;
    sizes->values[13] = 33;
    sizes->values[14] = 413;
    sizes->values[15] = 223;
    sizes->values[16] = 343;
    sizes->values[17] = 423;
    sizes->values[18] = 2293;
    sizes->values[19] = 313;

    uint_vector *profits = alloc_uint_vector(20);
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
    profits->values[10] = 403;
    profits->values[11] = 133;
    profits->values[12] = 223;
    profits->values[13] = 43;
    profits->values[14] = 203;
    profits->values[15] = 13;
    profits->values[16] = 323;
    profits->values[17] = 413;
    profits->values[18] = 2403;
    profits->values[19] = 313;

    double_vector *double_profits = alloc_double_vector(20);
    double_profits->values[0] = 1;
    double_profits->values[1] = 3;
    double_profits->values[2] = 4;
    double_profits->values[3] = 10;
    double_profits->values[4] = 20;
    double_profits->values[5] = 14;
    double_profits->values[6] = 20;
    double_profits->values[7] = 66;
    double_profits->values[8] = 61;
    double_profits->values[9] = 125;
    double_profits->values[10] = 403;
    double_profits->values[11] = 133;
    double_profits->values[12] = 223;
    double_profits->values[13] = 43;
    double_profits->values[14] = 203;
    double_profits->values[15] = 13;
    double_profits->values[16] = 323;
    double_profits->values[17] = 413;
    double_profits->values[18] = 2403;
    double_profits->values[19] = 313;

    uint_vector *result;

    result = bound_knapsack(sizes, profits, 1000, 5);

    CuAssertIntEquals(tc, 1306, uint_vector_scalar_mult(result, profits));

    free_uint_vector(result);

    result = approximate_bound_knapsack(sizes, double_profits, 1000, 5, 0.05);

    CuAssertTrue(tc, ( 1306 * 0.95 ) <= double_uint_vector_scalar_mult(double_profits, result) );

    free_uint_vector(result);

    free_uint_vector(profits);
    free_double_vector(double_profits);
    free_double_vector(sizes);
}

