/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "CuTest.h"
#include "linear_algebra.h"
#include "approximate_max_min_resource_sharing.h"

#include <stdio.h>

void Test_approximate_max_min_resource_sharing(CuTest *tc)
{
    double_matrix *A = alloc_double_matrix(2, 2);
    
    A->values[0 * 2 + 0] = 1;
    A->values[0 * 2 + 1] = 2;
    
    A->values[1 * 2 + 0] = 3;
    A->values[1 * 2 + 1] = 0;
    
    double_vector *optimum = approximate_max_min_resource_sharing(A,
                                                                  3,                                         
                                                                  0.25);
    printf("Optimum:\n");
    print_double_vector(optimum);
    
    free_double_matrix(A);
    free_double_vector(optimum);
}

void Test_calculate_optimum_condition(CuTest *tc)
{
    double_vector *b = alloc_double_vector(3);
    
    b->values[0] = 1.0;
    b->values[1] = 2.0;
    b->values[2] = 3.0;
    
    double optimum_condition = calculate_optimum_condition(b, 0.5, 5.0);
    
    CuAssertDblEquals(tc, 15.0, optimum_condition, 0.01);
    
    free_double_vector(b);
}
