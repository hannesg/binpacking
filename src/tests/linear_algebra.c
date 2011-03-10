/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "CuTest.h"
#include "linear_algebra.h"

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
