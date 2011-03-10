/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "float.h"

#include "CuTest.h"
#include "approximate_lp_solver.h"

void Test_approximate_lp_solver(CuTest *tc)
{
    uint_matrix *A = alloc_uint_matrix(2, 3);
    
    A->values[0 * 3 + 0] = 4;
    A->values[0 * 3 + 1] = 0;
    A->values[0 * 3 + 2] = 1;
    
    A->values[1 * 3 + 0] = 4;
    A->values[1 * 3 + 1] = 4;
    A->values[1 * 3 + 2] = 0;
    
    uint_vector *b = alloc_uint_vector(2);
    
    b->values[0] = 2;
    b->values[1] = 1;
    
    double_vector *x = approximate_lp_solver(A, b, 0.25, 10);
    
    CuAssertDblEquals(tc, 1.0, x->values[0], DBL_EPSILON);
    CuAssertDblEquals(tc, 0, x->values[1], DBL_EPSILON);
    CuAssertDblEquals(tc, 0, x->values[2], DBL_EPSILON);
    
    free_uint_matrix(A);
    free_uint_vector(b);
    free_double_vector(x);
}
