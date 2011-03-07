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
