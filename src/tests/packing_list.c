#include "CuTest.h"
#include "packing_list.h"
#include <stdio.h>

void Test_packing_is_initialized_correctly(CuTest *tc) {
    packing * pack = alloc_packing();
    CuAssertPtrNotNull(tc, pack);
}

void Test_packing_contains_items(CuTest *tc) {
    packing * pack = alloc_packing();

    insert_item(pack, 1);
    insert_item(pack, 2);
    insert_item(pack, 3);

    CuAssertTrue(tc, packing_contains_item(pack, 1));
    CuAssertTrue(tc, packing_contains_item(pack, 2));
    CuAssertTrue(tc, packing_contains_item(pack, 3));
    CuAssertTrue(tc, !packing_contains_item(pack, 4));
}

void Test_packing_cmp_equals(CuTest *tc) {
    packing * pack1 = alloc_packing();
    packing * pack2 = alloc_packing();

    insert_item(pack1, 1);
    insert_item(pack1, 2);
    insert_item(pack1, 3);

    insert_item(pack2, 3);
    insert_item(pack2, 1);
    insert_item(pack2, 2);

    CuAssertIntEquals(tc, 0, packing_cmp(pack1, pack2));
}

void Test_packing_cmp_lt1(CuTest *tc) {
    packing * pack1 = alloc_packing();
    packing * pack2 = alloc_packing();

    insert_item(pack1, 1);
    insert_item(pack1, 2);
    insert_item(pack1, 3);

    insert_item(pack2, 1);
    insert_item(pack2, 2);
    insert_item(pack2, 4);

    CuAssertTrue(tc, packing_cmp(pack1, pack2) < 0 );
}

void Test_packing_cmp_lt2(CuTest *tc) {
    packing * pack1 = alloc_packing();
    packing * pack2 = alloc_packing();

    insert_item(pack1, 1);
    insert_item(pack1, 2);
    insert_item(pack1, 3);

    insert_item(pack2, 4);
    insert_item(pack2, 1);
    insert_item(pack2, 2);

    CuAssertTrue(tc, packing_cmp(pack1, pack2) < 0 );
}

void Test_packing_cmp_lt3(CuTest *tc) {
    packing * pack1 = alloc_packing();
    packing * pack2 = alloc_packing();

    insert_item(pack1, 2);
    insert_item(pack1, 3);

    insert_item(pack2, 1);
    insert_item(pack2, 2);
    insert_item(pack2, 3);

    CuAssertTrue(tc, packing_cmp(pack1, pack2) < 0 );
}
