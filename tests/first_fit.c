/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include "CuTest.h"
#include "first_fit.h"
#include <stdio.h>

void Test_first_fit_step_should_work(CuTest *tc) {
    double items[] = {
            0.73,
            0.64,
            0.43,
            0.42,
            0.35,
            0.32,
            0.31,
            0.3,
            0.27,
            0.25,
            0.24,
            0.24,
            0.23,
            0.21,
            0.21,
            0.17,
            0.15,
            0.15,
            0.14,
            0.1
    };
    packing_list * pack_list = alloc_packing_list();
    first_fit_step(items,20,1,pack_list);

    first_fit_step(items,20,2,pack_list);

    first_fit_step(items,20,3,pack_list);

    CuAssertIntEquals(tc, 2, pack_list->size);
}


void Test_first_fit_should_work(CuTest *tc) {
    double items[] = {
            0.73,
            0.64,
            0.43,
            0.42,
            0.35,
            0.32,
            0.31,
            0.3,
            0.27,
            0.25,
            0.24,
            0.24,
            0.23,
            0.21,
            0.21,
            0.17,
            0.15,
            0.15,
            0.14,
            0.1
    };
    packing_list * pack_list = first_fit(items, 20);

    CuAssertIntEquals(tc, 6, pack_list->size);
}
