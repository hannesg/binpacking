/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include <time.h>
#include <assert.h>

#include "CuTest.h"
#include "binpacking.h"
#include "uint_matrix.h"

void Test_track_sort_should_work(CuTest *tc)
{
    unsigned int i=0;
    double last;
    double items[] = {
            0.32,
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

    free(positions);
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

int matrix_contains_exact_row(uint_matrix *A, unsigned int *row) {
    unsigned int i;
    for(i = 0; i < A->height; ++i) {
        unsigned int j;
        for(j = 0; j < A->width; j++) {
            if(A->values[A->width*i + j] != row[j]) {
                break;
            }
        }
        if(j == A->width) {
            return 1;
        }
    }
    return 0;
}

// this method is not required to be fast, just correct
int check_bin_packing_matrix(uint_matrix *A, double items[], unsigned int limit){
    assert( A != NULL );
    unsigned int i,j, x=0;
    double room;
    double fill;
    double min;
    int errors = 0;
    unsigned int max_value;
    unsigned int *row = calloc(A->width, sizeof(unsigned int));
    // check if every present packing is valid
    min = items[0];
    for( i = 0; i < A->width ; i++ ){
        if( items[i] < min ){
            min = items[i];
        }
    }
    // the algorithm rather packs a bit-too-small packings
    // this is due to double precision loss
    min += 0.0000000000000001;

    max_value = floor(PACKING_SIZE / min);
    if( max_value > limit ){
        max_value = limit;
    }

    for( i = 0; i < A->height ; i++ ){
        room = PACKING_SIZE;
        fill = 0;
        for( j = 0; j < A->width ; j++ ){
            if( A->values[ A->width*i + j ] > limit ){
                errors |= 4;
            }
            fill += A->values[ A->width*i + j ] * items[j];
            room -= A->values[ A->width*i + j ] * items[j];
        }
        if( fill > PACKING_SIZE ){
            printf("Packing too big: fill = %f\n", fill);
            print_submatrix(A, i, i+1, 0, A->width);
            errors |= 1;
        }
        if( room >= min ){
            printf("Packing too small: fill = %f\n",fill);
            print_submatrix(A, i, i+1, 0, A->width);
            errors |= 2;
        }
    }

    // check if at least some packings are present
    i = 1;
    while( i < max_value ){
        x = 0;
        while( x < A->width ){
            if( row[x] == 0 ){
                row[x] = i;
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
                break;
            }else{
                row[x] = 0;
            }
            x++;
        }
        if( x == A->width ){
            i++;
        }
    }

    free(row);

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

    double old_items[20];
    memcpy(old_items,items, sizeof(double)*20);
    unsigned int *positions = alloc_positions(20);

    track_sort_items(items,20, positions);

    uint_matrix *A = matrix_from_items(items,  20, 10);

    printf("A in %2i x %2i \n",A->width, A->height);
    CuAssertIntEquals(tc, 0, check_bin_packing_matrix(A,items, 10));

    free(positions);
    free_uint_matrix(A);
}

void Test_matrix_from_items_example1(CuTest *tc) {
    // This example contains both items from which more than limit fit into a bin
    // and items from which only less than limit fit into a bin.
    
    double items[] = {
        0.5,
        0.33,
        0.25
    };
    
    uint_matrix *A = matrix_from_items(items, 3, 3);
    
    CuAssertIntEquals(tc, 7, A->height);
    
    {
        unsigned int combination[] = {0, 0, 3};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {0, 1, 2};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {0, 2, 1};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {0, 3, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {1, 0, 2};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {1, 1, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {2, 0, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    free_uint_matrix(A);
}

void Test_matrix_from_items_example2(CuTest *tc) {
    // This example contains only items from which less than the limit fit into a bin.
    double items[] = {
        0.5,
        0.428,
        0.375
    };
    
    uint_matrix *A = matrix_from_items(items, 3, 3);
    
    CuAssertIntEquals(tc, 6, A->height);
    
    {
        unsigned int combination[] = {0, 0, 2};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {0, 1, 1};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {0, 2, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {1, 0, 1};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {1, 1, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {2, 0, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
        
    free_uint_matrix(A);
}

void Test_matrix_from_items_example3(CuTest *tc) {
    // This examle contains only items from which more than the limit fit into a bin.
    double items[] = {
        0.33,
        0.25,
        0.2
    };
    
    uint_matrix *A = matrix_from_items(items, 3, 3);
    
    CuAssertIntEquals(tc, 9, A->height);
    
    {
        unsigned int combination[] = {0, 1, 3};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {0, 2, 2};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {0, 3, 1};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {1, 0, 3};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {1, 1, 2};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {1, 2, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {2, 0, 1};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {2, 1, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    {
        unsigned int combination[] = {3, 0, 0};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    free_uint_matrix(A);
}

void Test_matrix_from_items_example4(CuTest *tc) {
    // All fit
    double items[] = {
        0.111,
        0.100,
        0.05
    };
    
    uint_matrix *A = matrix_from_items(items, 3, 3);

    CuAssertIntEquals(tc, 1, A->height);
    
    {
        unsigned int combination[] = {3, 3, 3};
        CuAssertTrue(tc, matrix_contains_exact_row(A, combination));
    }
    
    free_uint_matrix(A);
}

void Test_binpacking(CuTest *tc)
{
    double items[] = {
        0.25,
        0.1,
        0.2,
        0.7,
        0.25,
        0.25,
        0.25
    };
    
    packing_list *result = binpacking(items, 0.25, 7, Good, 1);
    CuAssertIntEquals(tc, 3, result->size);
    print_packing_list(result);
    free_packing_list(result);
    
    result = binpacking(items, 0.25, 7, Ugly, 1);
    CuAssertIntEquals(tc, 3, result->size);
    print_packing_list(result);
    free_packing_list(result);
}

void Test_binpacking_all_small(CuTest *tc)
{
    double items[] = {
        0.09,
        0.10,
        0.20,
        0.05,
        0.01,
        0.21,
        0.19,
        0.12,
        0.23,
        0.09,
        0.09,
        0.20,
        0.06,
        0.06,
        0.05,
        0.02,
        0.01,
        0.05,
        0.02,
        0.12,
        0.11,
        0.13,
        0.14,
        0.14,
        0.001
    };
    
    packing_list *result = binpacking(items, 0.5, 25, Good, 1);
    CuAssertIntEquals(tc, 3, result->size);
    print_packing_list(result);
    free_packing_list(result);
    
    result = binpacking(items, 0.5, 25, Ugly, 1);
    CuAssertIntEquals(tc, 3, result->size);
    print_packing_list(result);
    free_packing_list(result);
}

void Test_binpacking_k_larger_1(CuTest *tc)
{
    double items[] = {
        0.95383,
        0.91409,
        0.82553,
        0.81573,
        0.80621,
        
        0.79471,
        0.77701,
        0.73309,
        0.72229,
        0.71332,
        
        0.68805,
        0.63351,
        0.63205,
        0.59021,
        0.54370,
        
        0.52509,
        0.49393,
        0.48782,
        0.47655,
        0.46857,
        
        0.46523,
        0.46219,
        0.46036,
        0.45598,
        0.44385,
        
        0.43423,
        0.43112,
        0.42865,
        0.42197,
        0.41972,
        
        0.41905,
        0.41837,
        0.41714,
        0.41505,
        0.40570,
        
        0.39944,
        0.39261,
        0.38895,
        0.38666,
        0.38536,
        
        0.38520
    };
    
    packing_list *result = binpacking(items, 0.5, 41, Good, 1);
    printf("We need %i bins.\n", result->size);
    print_packing_list(result);
    free_packing_list(result);
    
    result = binpacking(items, 0.5, 41, Ugly, 1);
    printf("We need %i bins.\n", result->size);
    print_packing_list(result);
    free_packing_list(result);
}
