/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "CuTest.h"
#include "types.h"
#include "double_matrix.h"
#include "double_vector.h"
#include "uint_matrix.h"
#include "uint_vector.h"

#include <stdio.h>
#include <float.h>

void Test_alloc_double_vector(CuTest *tc)
{
    double_vector *vector = (double_vector *) alloc_double_vector(5);
    CuAssertPtrNotNull(tc, vector);
    CuAssertPtrNotNull(tc, vector->values);
    free_double_vector(vector);
}

void Test_alloc_double_matrix(CuTest *tc)
{
    double_matrix *matrix = (double_matrix *) alloc_double_matrix(5, 6);
    CuAssertPtrNotNull(tc, matrix);
    CuAssertPtrNotNull(tc, matrix->values);
    free_double_matrix(matrix);
}

void Test_vector_matrix_mult(CuTest *tc)
{
    // Alloc
    double_vector *vector = (double_vector *) alloc_double_vector(3);
    double_matrix *matrix = (double_matrix *) alloc_double_matrix(3, 2);
    
    // Initialize vector
    vector->values[0] = 1.0;
    vector->values[1] = 2.0;
    vector->values[2] = 3.0;
    
    // Initialize matrix
    matrix->values[0 * 2 + 0] = 2.0;
    matrix->values[0 * 2 + 1] = 0.0;
    matrix->values[1 * 2 + 0] = 1.0;
    matrix->values[1 * 2 + 1] = 3.0;
    matrix->values[2 * 2 + 0] = -1.0;
    matrix->values[2 * 2 + 1] = -2.0;
    
    // Calculation
    double_vector *result = vector_matrix_mult(vector, matrix);
    
    // Test
    CuAssertIntEquals(tc, 2, result->size);
    
    CuAssertDblEquals(tc, 1.0, result->values[0], 0.001);
    CuAssertDblEquals(tc, 0.0, result->values[1], 0.001);
    
    // Cleanup
    free_double_vector(vector);
    free_double_matrix(matrix);
    free_double_vector(result);
}

void Test_vector_transposed_matrix_mult(CuTest *tc)
{
    // Alloc
    double_vector *vector = (double_vector *) alloc_double_vector(3);
    double_matrix *matrix = (double_matrix *) alloc_double_matrix(2, 3);
    
    // Initialize vector
    vector->values[0] = 1.0;
    vector->values[1] = 2.0;
    vector->values[2] = 3.0;
    
    // Initialize matrix
    matrix->values[0 * 3 + 0] = 2.0;
    matrix->values[1 * 3 + 0] = 0.0;
    matrix->values[0 * 3 + 1] = 1.0;
    matrix->values[1 * 3 + 1] = 3.0;
    matrix->values[0 * 3 + 2] = -1.0;
    matrix->values[1 * 3 + 2] = -2.0;
    
    // Calculation
    double_vector *result = vector_transposed_matrix_mult(vector, matrix);
    
    // Test
    CuAssertIntEquals(tc, 2, result->size);
    
    CuAssertDblEquals(tc, 1.0, result->values[0], 0.001);
    CuAssertDblEquals(tc, 0.0, result->values[1], 0.001);
    
    // Cleanup
    free_double_vector(vector);
    free_double_matrix(matrix);
    free_double_vector(result);
}

void Test_matrix_vector_mult(CuTest *tc)
{
    // Alloc
    double_vector *vector = (double_vector *) alloc_double_vector(3);
    double_matrix *matrix = (double_matrix *) alloc_double_matrix(2, 3);
    
    // Initialize vector
    vector->values[0] = 1.0;
    vector->values[1] = 2.0;
    vector->values[2] = 3.0;
    
    // Initialize matrix
    matrix->values[0 * 3 + 0] = 2.0;
    matrix->values[0 * 3 + 1] = 0.0;
    matrix->values[0 * 3 + 2] = 1.0;
    matrix->values[1 * 3 + 0] = 3.0;
    matrix->values[1 * 3 + 1] = -1.0;
    matrix->values[1 * 3 + 2] = -2.0;
    
    double_vector *result = matrix_vector_mult(matrix, vector);
    
    // Test
    CuAssertIntEquals(tc, 2, result->size);
    
    CuAssertDblEquals(tc, 2.0 * 1.0 + 0.0 * 2.0 + 1.0 * 3.0, result->values[0], DBL_EPSILON);
    CuAssertDblEquals(tc, 3.0 * 1.0 - 1.0 * 2.0 - 2.0 * 3.0, result->values[1], DBL_EPSILON);
    
    // Cleanup
    free_double_vector(vector);
    free_double_vector(result);
    free_double_matrix(matrix);
}

void Test_transposed_matrix_vector_mult(CuTest *tc)
{
    // Alloc
    double_vector *vector = (double_vector *) alloc_double_vector(3);
    double_matrix *matrix = (double_matrix *) alloc_double_matrix(3, 2);
    
    // Initialize vector
    vector->values[0] = 1.0;
    vector->values[1] = 2.0;
    vector->values[2] = 3.0;
    
    // Initialize matrix
    matrix->values[0 * 2 + 0] = 2.0;
    matrix->values[1 * 2 + 0] = 0.0;
    matrix->values[2 * 2 + 0] = 1.0;
    
    matrix->values[0 * 2 + 1] = 3.0;
    matrix->values[1 * 2 + 1] = -1.0;
    matrix->values[2 * 2 + 1] = -2.0;
    
    double_vector *result = transposed_matrix_vector_mult(matrix, vector);
    
    // Test
    CuAssertIntEquals(tc, 2, result->size);
    
    CuAssertDblEquals(tc, 2.0 * 1.0 + 0.0 * 2.0 + 1.0 * 3.0, result->values[0], DBL_EPSILON);
    CuAssertDblEquals(tc, 3.0 * 1.0 - 1.0 * 2.0 - 2.0 * 3.0, result->values[1], DBL_EPSILON);
    
    // Cleanup
    free_double_vector(vector);
    free_double_vector(result);
    free_double_matrix(matrix);
}

void Test_vector_min(CuTest *tc)
{
    // Alloc
    double_vector *x = alloc_double_vector(5);
    
    x->values[0] = -5.0;
    x->values[1] = 0;
    x->values[2] = 0.12;
    x->values[3] = -12.2;
    x->values[4] = -8;
    
    // Calculate
    double minimum = vector_min(x);
    
    // Test
    CuAssertDblEquals(tc, -12.2, minimum, DBL_EPSILON);
    
    // Cleanup
    free_double_vector(x);
}

void Test_vector_scalar_mult(CuTest *tc)
{
    // Alloc
    double_vector *a = alloc_double_vector(3);
    double_vector *b = alloc_double_vector(3);
    
    a->values[0] = 1.0;
    a->values[1] = 0.2;
    a->values[2] = -0.3;
    b->values[0] = 0.1;
    b->values[1] = -0.2;
    b->values[2] = 0.01;
    
    // Calculate
    double scalar_product = vector_scalar_mult(a, b);
    
    // Test
    CuAssertDblEquals(tc, 1.0 * 0.1 - 0.2 * 0.2 - 0.3 * 0.01, scalar_product, DBL_EPSILON);
    
    // Cleanup
    free_double_vector(a);
    free_double_vector(b);
}


void Test_fill_double_vector(CuTest *tc)
{
    // Alloc
    double_vector *vector = alloc_double_vector(10);
    fill_double_vector(vector, 10.0);
    
    // Test
    CuAssertIntEquals(tc, 10, vector->size);

    int i;
    for(i = 0; i < 10; ++i) {
        CuAssertDblEquals(tc, 10.0, vector->values[i], DBL_EPSILON);
    }
    
    // Cleaning up
    free_double_vector(vector);
}

void Test_vector_vector_add_assignment(CuTest *tc)
{
    // Alloc
    double_vector *a = alloc_double_vector(3);
    double_vector *b = alloc_double_vector(3);
    
    a->values[0] = 1.0;
    a->values[1] = 0.5;
    a->values[2] = 0.3;
    
    b->values[0] = 0.4;
    b->values[1] = 2.1;
    b->values[2] = 1.5;
    
    // Run
    vector_vector_add_assignment(a, b);
    
    // Test
    CuAssertIntEquals(tc, 3, a->size);

    CuAssertDblEquals(tc, 1.0 + 0.4, a->values[0], DBL_EPSILON);
    CuAssertDblEquals(tc, 0.5 + 2.1, a->values[1], DBL_EPSILON);
    CuAssertDblEquals(tc, 0.3 + 1.5, a->values[2], DBL_EPSILON);
    
    // Cleaning up
    free_double_vector(a);
    free_double_vector(b);
}

void Test_number_vector_mult_assignment(CuTest *tc)
{
    // Alloc
    double_vector *a = alloc_double_vector(3);
    
    a->values[0] = 1.0;
    a->values[1] = 0.5;
    a->values[2] = 0.3;
    
    // Run
    number_vector_mult_assignment(2.0, a);
    
    // Test 
    CuAssertIntEquals(tc, 3, a->size);

    CuAssertDblEquals(tc, 1.0 * 2.0, a->values[0], DBL_EPSILON);
    CuAssertDblEquals(tc, 0.5 * 2.0, a->values[1], DBL_EPSILON);
    CuAssertDblEquals(tc, 0.3 * 2.0, a->values[2], DBL_EPSILON);
    
    // Cleaning up
    free_double_vector(a);
}

void Test_double_vector_cmp_different_size(CuTest *tc)
{
    double_vector *a = alloc_double_vector(5);
    double_vector *b = alloc_double_vector(6);
    
    int equal = double_vector_cmp(a, b);
    
    CuAssertIntEquals(tc, -1, equal);
    
    free_double_vector(a);
    free_double_vector(b);
}

void Test_double_vector_cmp_not_equal(CuTest *tc)
{
    double_vector *a = alloc_double_vector(3);
    double_vector *b = alloc_double_vector(3);
    
    fill_double_vector(a, 0.1);
    fill_double_vector(b, 0.1);
    
    a->values[1] = 0.2;
    
    int equal = double_vector_cmp(a, b);
    
    CuAssertIntEquals(tc, 2, equal);
    
    free_double_vector(a);
    free_double_vector(b);
}

void Test_double_vector_cmp_equal(CuTest *tc)
{
    double_vector *a = alloc_double_vector(3);
    double_vector *b = alloc_double_vector(3);
    
    fill_double_vector(a, 0.1);
    fill_double_vector(b, 0.1);
    
    a->values[1] = 0.2;
    b->values[1] = 0.2;
    
    int equal = double_vector_cmp(a, b);
    
    CuAssertIntEquals(tc, 0, equal);
    
    free_double_vector(a);
    free_double_vector(b);
}

void Test_uint_matrix_vector_division(CuTest *tc)
{
    uint_matrix *A = alloc_uint_matrix(3, 2);
    
    A->values[0 * 2 + 0] = 1;
    A->values[0 * 2 + 1] = 2;
    
    A->values[1 * 2 + 0] = 3;
    A->values[1 * 2 + 1] = 4;
    
    A->values[2 * 2 + 0] = 5;
    A->values[2 * 2 + 1] = 6;
    
    uint_vector *b = alloc_uint_vector(3);
    b->values[0] = 1;
    b->values[1] = 2;
    b->values[2] = 3;
    
    double_matrix *result = uint_matrix_vector_division(A, b);
    
    CuAssertDblEquals(tc, 1.0 / 1.0, result->values[0 * 2 + 0], DBL_EPSILON);
    CuAssertDblEquals(tc, 2.0 / 1.0, result->values[0 * 2 + 1], DBL_EPSILON);
    
    CuAssertDblEquals(tc, 3.0 / 2.0, result->values[1 * 2 + 0], DBL_EPSILON);
    CuAssertDblEquals(tc, 4.0 / 2.0, result->values[1 * 2 + 1], DBL_EPSILON);
    
    CuAssertDblEquals(tc, 5.0 / 3.0, result->values[2 * 2 + 0], DBL_EPSILON);
    CuAssertDblEquals(tc, 6.0 / 3.0, result->values[2 * 2 + 1], DBL_EPSILON);
    
    free_uint_matrix(A);
    free_uint_vector(b);
    free_double_matrix(result);
}

void Test_uint_transposed_matrix_vector_division(CuTest *tc)
{
    uint_matrix *A = alloc_uint_matrix(2, 3);
    
    A->values[0 * 3 + 0] = 1;
    A->values[0 * 3 + 1] = 2;
    A->values[0 * 3 + 2] = 3;
    
    A->values[1 * 3 + 0] = 4;
    A->values[1 * 3 + 1] = 5;
    A->values[1 * 3 + 2] = 6;
    
    uint_vector *b = alloc_uint_vector(3);
    b->values[0] = 1;
    b->values[1] = 2;
    b->values[2] = 3;
    
    double_matrix *result = uint_transposed_matrix_vector_division(A, b);
    
    CuAssertDblEquals(tc, 1.0 / 1.0, result->values[0 * 3 + 0], DBL_EPSILON);
    CuAssertDblEquals(tc, 2.0 / 2.0, result->values[0 * 3 + 1], DBL_EPSILON);
    CuAssertDblEquals(tc, 3.0 / 3.0, result->values[0 * 3 + 2], DBL_EPSILON);
    
    CuAssertDblEquals(tc, 4.0 / 1.0, result->values[1 * 3 + 0], DBL_EPSILON);
    CuAssertDblEquals(tc, 5.0 / 2.0, result->values[1 * 3 + 1], DBL_EPSILON);
    CuAssertDblEquals(tc, 6.0 / 3.0, result->values[1 * 3 + 2], DBL_EPSILON);
    
    free_uint_matrix(A);
    free_uint_vector(b);
    free_double_matrix(result);
}

void Test_double_vector_order(CuTest *tc)
{
    double_vector *vector = alloc_double_vector(9);
    
    vector->values[0] = 0.21;
    vector->values[1] = 0.20;
    vector->values[2] = 0.41;
    vector->values[3] = 0.09;
    vector->values[4] = 0.12;
    vector->values[5] = 0.01;
    vector->values[6] = 0.00;
    vector->values[7] = 0.9;
    vector->values[8] = 0.3;
    
    uint_vector *result = double_vector_order(vector);
    
    CuAssertIntEquals(tc, 7, result->values[0]);
    CuAssertIntEquals(tc, 2, result->values[1]);
    CuAssertIntEquals(tc, 8, result->values[2]);
    CuAssertIntEquals(tc, 0, result->values[3]);
    CuAssertIntEquals(tc, 1, result->values[4]);
    CuAssertIntEquals(tc, 4, result->values[5]);
    CuAssertIntEquals(tc, 3, result->values[6]);
    CuAssertIntEquals(tc, 5, result->values[7]);
    CuAssertIntEquals(tc, 6, result->values[8]);
    
    free_uint_vector(result);
    free_double_vector(vector);
}

void Test_uint_matrix_change_height(CuTest *tc)
{
    uint_matrix *A = alloc_uint_matrix(10, 8);
    
    uint_matrix_change_height(A, 23);
    CuAssertIntEquals(tc, 40, A->array_height);
    
    uint_matrix_change_height(A, 1024);
    CuAssertIntEquals(tc, 2048, A->array_height);

    free_uint_matrix(A);
}

void Test_uint_matrix_append_row(CuTest *tc)
{
    uint_vector *vector = alloc_uint_vector(3);
    vector->values[0] = 7;
    vector->values[1] = 8;
    vector->values[2] = 9;
    
    uint_matrix *A = alloc_uint_matrix(2, 3);
    
    A->values[0 * 3 + 0] = 1;
    A->values[0 * 3 + 1] = 2;
    A->values[0 * 3 + 2] = 3;
    
    A->values[1 * 3 + 0] = 4;
    A->values[1 * 3 + 1] = 5;
    A->values[1 * 3 + 2] = 6;
    
    // First time
    uint_matrix_append_row(A, vector);
    
    // Sizes
    CuAssertIntEquals(tc, 3, A->height);
    CuAssertIntEquals(tc, 4, A->array_height);
    
    // Values
    CuAssertIntEquals(tc, 7, A->values[2 * 3 + 0]);
    CuAssertIntEquals(tc, 8, A->values[2 * 3 + 1]);
    CuAssertIntEquals(tc, 9, A->values[2 * 3 + 2]);
    
    // Second time
    uint_matrix_append_row(A, vector);
    
    // Sizes
    CuAssertIntEquals(tc, 4, A->height);
    CuAssertIntEquals(tc, 4, A->array_height);
    
    // Values
    CuAssertIntEquals(tc, 7, A->values[3 * 3 + 0]);
    CuAssertIntEquals(tc, 8, A->values[3 * 3 + 1]);
    CuAssertIntEquals(tc, 9, A->values[3 * 3 + 2]);

    free_uint_vector(vector);
    free_uint_matrix(A);
}

void Test_uint_matrix_ensure_row_existence(CuTest *tc)
{
    uint_vector *vector = alloc_uint_vector(3);
    vector->values[0] = 7;
    vector->values[1] = 8;
    vector->values[2] = 9;
    
    uint_matrix *A = alloc_uint_matrix(2, 3);
    
    A->values[0 * 3 + 0] = 1;
    A->values[0 * 3 + 1] = 2;
    A->values[0 * 3 + 2] = 3;
    
    A->values[1 * 3 + 0] = 4;
    A->values[1 * 3 + 1] = 5;
    A->values[1 * 3 + 2] = 6;
    
    // Not in there:
    CuAssertIntEquals(tc, 2, uint_matrix_ensure_row_existence(A, vector));
    CuAssertIntEquals(tc, 3, A->height);
    CuAssertIntEquals(tc, 7, A->values[2 * 3 + 0]);
    CuAssertIntEquals(tc, 8, A->values[2 * 3 + 1]);
    CuAssertIntEquals(tc, 9, A->values[2 * 3 + 2]);
    
    // In there:
    vector->values[0] = 4;
    vector->values[1] = 5;
    vector->values[2] = 6;
    CuAssertIntEquals(tc, 1, uint_matrix_ensure_row_existence(A, vector));
    CuAssertIntEquals(tc, 3, A->height);
    CuAssertIntEquals(tc, 4, A->values[1 * 3 + 0]);
    CuAssertIntEquals(tc, 5, A->values[1 * 3 + 1]);
    CuAssertIntEquals(tc, 6, A->values[1 * 3 + 2]);
    
    // Didn't we insert something a while ago?
    vector->values[0] = 7;
    vector->values[1] = 8;
    vector->values[2] = 9;
    
    CuAssertIntEquals(tc, 2, uint_matrix_ensure_row_existence(A, vector));
    CuAssertIntEquals(tc, 3, A->height);
    CuAssertIntEquals(tc, 7, A->values[2 * 3 + 0]);
    CuAssertIntEquals(tc, 8, A->values[2 * 3 + 1]);
    CuAssertIntEquals(tc, 9, A->values[2 * 3 + 2]);

    free_uint_vector(vector);
    free_uint_matrix(A);
}
