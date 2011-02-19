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

void print_submatrix(uint_matrix *A, unsigned int start_i, unsigned int end_i, unsigned int start_j, unsigned int end_j){
    unsigned int i,j;
    for( i = start_i; i < end_i; i++ ){
        for( j = start_j ; j < end_j ; j++ ){
            printf("%6i ", A->values[ A->width*i + j ]);
        }
        printf("\n");
    }
}

void print_row(unsigned int *row, unsigned int n){
    unsigned int i;
    for( i = 0; i < n; i++ ){
        printf("%6i ",row[i]);
    }
    printf("\n");
}

int matrix_contains_higher_row(uint_matrix *A, unsigned int *row){
    unsigned int i,j;
    for( i = 0; i < A->height ; i++ ){
        for( j = 0; j < A->width ; j++ ){
            if( A->values[ A->width*i + j ] < row[j] ){
                break;
            }
        }
        if( j == A->width ){
            return 1;
        }
    }
    return 0;
}

// this method is not required to be fast, just correct
int check_bin_packing_matrix(uint_matrix *A, double items[], unsigned int limit){
    unsigned int i,j, x,y;
    double room;
    double min;
    int errors = 0;
    unsigned int max_value;
    unsigned int *row = malloc(sizeof(unsigned int) * A->width);
    // check if every present packing is valid
    min = items[0];
    for( i = 0; i < A->width ; i++ ){
        if( items[i] < min ){
            min = items[i];
        }
    }

    max_value = floor(PACKING_SIZE / min);
    if( max_value > limit ){
        max_value = limit;
    }

    for( i = 0; i < A->height ; i++ ){
        room = PACKING_SIZE;
        for( j = 0; j < A->width ; j++ ){
            if( A->values[ A->width*i + j ] > limit ){
                errors |= 4;
            }
            room -= A->values[ A->width*i + j ] * items[j];
        }
        if( room < 0 ){
            printf("Packing too big:\n");
            print_submatrix(A, i, i+1, 0, A->width);
            errors |= 1;
        }
        if( room >= min ){
            printf("Packing too small:\n");
            print_submatrix(A, i, i+1, 0, A->width);
            errors |= 2;
        }
    }

    // check if every packing is present
    x = 0;
    while( x < A->width ){
        row[x]++;
        if( row[x] > max_value ){
            row[x] = 0;
            x++;
        }else{
            // check if this row is possible
            room = PACKING_SIZE;
            for( j = 0; j < A->width ; j++ ){
                room -= row[j] * items[j];
            }
            if( room >= 0 ){
                // this packing is small enough
                // there has to be a containing packing
                if( !matrix_contains_higher_row(A, row) ){
                    printf("No Packing includes:\n");
                    print_row( row, A->width);
                    errors |= 8;
                }
            }
        }

    }

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
    CuAssertIntEquals(tc, 0, check_bin_packing_matrix(A,items, 10));
}

