/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "CuTest.h"
#include "../linear_algebra.h"
#include "../approximate_block_solver.h"

#include <stdio.h>

void Test_approximate_block_solver(CuTest *tc)
{
    double_vector *p = alloc_double_vector(2);
    p->values[0] = 0.5;
    p->values[1] = 1.0;
    double_matrix *A = alloc_double_matrix(2, 3);
    A->values[0] = 1.0;
    A->values[1] = 2.0;
    A->values[2] = 3.0;
    
    A->values[3] = 2.0;
    A->values[4] = 2.0;
    A->values[5] = 3.0;
    
    double_vector *opt = approximate_block_solver(A, p, 5, 0.001);
    
    CuAssertDblEquals(tc, 0.0, opt->values[0], 0.01);
    CuAssertDblEquals(tc, 0.0, opt->values[1], 0.01);
    CuAssertDblEquals(tc, 5.0, opt->values[2], 0.01);
    
    free_double_vector(p);
    free_double_matrix(A);
    free_double_vector(opt);
}
