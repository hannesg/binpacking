/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include "CuTest.h"
#include "binpacking.h"

void Test_track_sort_should_work(CuTest *tc)
{
    unsigned int i=0;
    double last;
    double items[] = {
            0.32,
            0.31,
            0.3,
            0.27,
            0.25,
            0.1,
            0.21,
            0.17,
            0.24,
            0.73,
            0.64,
            0.43,
            0.21,
            0.24,
            0.23,
            0.14,
            0.42,
            0.35,
            0.15,
            0.15
    };
    double old_items[20];
    memcpy(old_items,items, sizeof(double)*20);
    unsigned int *positions = alloc_positions(20);

    track_sort_items(items,20, positions);

    last = items[0];
    while( i < 20 ){
        CuAssertDblEquals(tc, items[i], old_items[positions[i]], 0 );
        CuAssertTrue(tc, items[i] <= last);
        last = items[i];
        i++;
    }
}


// this method is not required to be fast, just correct
int check_bin_packing_matrix(uint_matrix *A, double items[]){
    unsigned int i,j;
    double room;
    double min;
    int errors = 0;
    // check if every present packing is valid
    min = items[0];
    for( i = 0; i < A->width ; i++ ){
        if( items[i] < min ){
            min = items[i];
        }
    }
    for( i = 0; i < A->height ; i++ ){
        room = PACKING_SIZE;
        for( j = 0; j < A->width ; j++ ){
            room -= A->values[ A->width*i + j ] * items[j];
        }
        if( room < 0 ){
            errors |= 1;
        }
        if( room >= min ){
            errors |= 2;
        }
    }

    // check if every packing is present



    return errors;
}

void Test_matrix_from_items_should_work(CuTest *tc)
{
    double items[] = {
            0.32,
            0.31,
            0.3,
            0.27,
            0.25,
            0.1,
            0.21,
            0.17,
            0.24,
            0.73,
            0.64,
            0.43,
            0.21,
            0.24,
            0.23,
            0.14,
            0.42,
            0.35,
            0.15,
            0.15
    };
    uint_matrix *A = matrix_from_items(items,  20, 10);
    unsigned int i = 0, j = 0;

    printf("A in %2i x %2i \n",A->width, A->height);
    CuAssertIntEquals(tc, 0, check_bin_packing_matrix(A,items));
}

