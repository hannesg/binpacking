/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "CuTest.h"
#include "linear_algebra.h"

#include <stdio.h>

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
    
    // Inintialize matrix
    matrix->values[0 * 2 + 0] = 2.0;
    matrix->values[0 * 2 + 1] = 0.0;
    matrix->values[1 * 2 + 0] = 1.0;
    matrix->values[1 * 2 + 1] = 3.0;
    matrix->values[2 * 2 + 0] = -1.0;
    matrix->values[2 * 2 + 1] = -2.0;
    
    // Calculation
    double_vector *result = vector_matrix_mult(vector, matrix);
    
    // Test
    CuAssertDblEquals(tc, 1.0, result->values[0], 0.001);
    CuAssertDblEquals(tc, 0.0, result->values[1], 0.001);
    
    // Cleanup
    free_double_vector(vector);
    free_double_matrix(matrix);
    free_double_vector(result);
}

