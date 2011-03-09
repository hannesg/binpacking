/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "CuTest.h"
#include "linear_algebra.h"
#include "approximate_max_min_resource_sharing_p.h"
#include "approximate_max_min_resource_sharing.h"
#include <float.h>

#include <stdio.h>

void Test_approximate_max_min_resource_sharing(CuTest *tc)
{
    double_matrix *A = alloc_double_matrix(2, 2);
    double epsilon = 0.25;
    
    A->values[0 * 2 + 0] = 1;
    A->values[0 * 2 + 1] = 2;
    
    A->values[1 * 2 + 0] = 3;
    A->values[1 * 2 + 1] = 0;
    
    max_min_resource_sharing_solution *solution
        = approximate_max_min_resource_sharing(A, 3, epsilon);
    double_vector *function_solution = matrix_vector_mult(A, solution->vector);
    CuAssertTrue(tc, !double_vector_cmp_delta(solution->function_solution, function_solution, 0.0000000000001));
    CuAssertIntEquals(tc, vector_min(function_solution), solution->function_solution_min);
    
    double_vector *real_optimum = alloc_double_vector(2);
    real_optimum->values[0] = 1.5;
    real_optimum->values[1] = 1.5;
    double_vector *optimum_function_solution = matrix_vector_mult(A, real_optimum);
    double optimum_min = vector_min(optimum_function_solution);
    
    CuAssertDblEquals(tc, optimum_min, solution->function_solution_min, optimum_min * epsilon); 
    
    free_double_matrix(A);
    free_max_min_resource_sharing_solution(solution);
    free_double_vector(real_optimum);
    free_double_vector(optimum_function_solution);
}

void Test_calculate_optimum_condition(CuTest *tc)
{
    double_vector *b = alloc_double_vector(3);
    
    b->values[0] = 1.0;
    b->values[1] = 2.0;
    b->values[2] = 3.0;
    
    double optimum_condition = calculate_optimum_condition(b, 0.5, 5.0);
    
    CuAssertDblEquals(tc, 2.55556, optimum_condition, 0.001);
    
    free_double_vector(b);
}

void Test_find_optimum(CuTest *tc)
{
    double_vector *b = alloc_double_vector(3);
    
    b->values[0] = 1.0;
    b->values[1] = 2.0;
    b->values[2] = 3.0;
    
    double optimum = find_optimum(b, 5.0);
    
    CuAssertDblEquals(tc, 0.26131, optimum, 0.01);
    
    free_double_vector(b);
}
