/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include <assert.h>

#include "binpacking.h"

const int MAX_BIN_NUMBER = 10;

packing_list * binpacking(double items_in[], double epsilon, unsigned int n){

    /*
     * A list of positions which will be used in the last step to revert the sorting.
     */
    unsigned int *positions = alloc_positions(n);

    /*
     * A sorted copy of the items.
     */
    double *items = malloc(sizeof(double) * n);

    /*
     * The partitioned items.
     */
    double *partition_items;

    /*
     * The partitioned sizes.
     */
    unsigned int *partition_sizes;


    /*
     * Items smaller than delta will be ignored first and will be inserted later using first fit.
     */
    double delta = epsilon / 2;

    /*
     * Biggest n with items[n] >= delta .
     * This is n'+1 .
     */
    unsigned int min_small_n = 0;

    /*
     * The resulting packing list.
     */
    packing_list * result;

    /*
     * The number items in an item partition.
     */
    unsigned int k;

    /*
     * The number of item partitions.
     */
    unsigned int m;

    /*
     * The LP-Matrix
     */
    uint_matrix *A;

    /*
     * The LP-Target
     */
    uint_vector *b;

    /*
     * The LP-Solution
     */
    double_vector *x;

    /*
     * auxiliary variables
     */
    unsigned int g = 0, h = 0, i = 0, j = 0, aij;
    packing *pack;

    // copy and sort the given items
    memcpy(items, items_in, sizeof(double) * n);
    track_sort_items(items, n, positions);

    // determine the border between normal and small items
    while(min_small_n < n && items[min_small_n] >= delta){
        min_small_n++;
    }

    if(min_small_n <= 1){
        // if max_normal_n == 0 then every item is small and we cannot partition the input.
        // if max_normal_n == 1 then k will be 0, which will result in empty partitions.
        //      => simply first fit them!
        //         since most items are quite small, this will give acceptable results!
        free(positions);
        free(items);
        return first_fit(items_in, n);
    }

    k = ceil((delta * delta * (min_small_n - 1))/2);
    // k > 0 since min_small_n > 1
    // TODO: If k == 1 we will win nothing by partitioning the items. Fallback?
    m = floor((min_small_n - 1)/k);

    // create the partitions
    // TODO: Do we always need m partitions? Maybe we need only m-1.
    partition_items = malloc(m * sizeof(double));
    partition_sizes = malloc(m * sizeof(unsigned int));

    i = 0;
    while(i < m) {
        unsigned int partition_start = (i + 1) * k;
        unsigned int partition_size = min_small_n - partition_start;

        if(partition_size > k) {
            partition_size = k;
        }

        partition_items[i] = items[ partition_start ];
        partition_sizes[i] = partition_size;

        i++;
    }

    // this matrix contains all possible packings
    A = matrix_from_items(partition_items, m, k);

    b = alloc_uint_vector(m);
    fill_uint_vector(b, k);

    // solve the LP approximately
    x = approximate_lp_solver(A, b, delta, MAX_BIN_NUMBER);
    // dummy:
//     x = alloc_double_vector(A->width);

    // pack the solutions
    result = alloc_packing_list();

    i = 0;
    while( i < x->size ){
        g = ceil(x->values[i]);
        while( g > 0 ){
            // generate packing
            pack = alloc_packing();
            j = 0;
            while( j < m ){
                aij = uint_matrix_elem(A,i,j);
                if( aij > 0){
                    h = 0;
                    while( h < aij ){
                        // we pack the original items directly or a smaller one
                        // depending on whether we have already packed a bigger one
                        if( partition_sizes[j] > 0 ){
                            // we haven't packed all items in this partition
                            partition_sizes[j]--;
                            insert_item(pack, positions[ (j+1)*k + partition_sizes[j] ] );
                        }
                        h++;
                    }
                }
                j++;
            }
            if( pack->size == 0 ){
                free_packing(pack);
            }else{
                insert_packing(result, pack, 1);
            }
            g--;
        }
        i++;
    }
    // assert: every partition_sizes == 0

    // pack the big items
    i = 0;
    while( i < k ){
        pack = alloc_packing();
        insert_item(pack, positions[i]);
        insert_packing(result, pack, 1);
        i++;
    }

    // pack the small items
    i = min_small_n;
    while( i < n ){
        first_fit_step(items_in, n, positions[i], result);
        i++;
    }

    // rewrite the positions in the solution
    // is now unnecessary
    //renumber_packing_list(result, positions);

    // free memory
    free_uint_matrix(A);
    free_uint_vector(b);
    free_double_vector(x);
    free(items);
    free(partition_items);
    free(partition_sizes);
    free(positions);

    // done!
    return result;
}

void track_sort_items(double items[], unsigned int n, unsigned int positions[])
{
    double temp;
    unsigned int left = 1, right = n - 1, temp_pos;
    if (n <= 1) {
        return;
    }
    
    while(left < right && items[left] >= items[0]) {
        left++;
    }
    while(items[right] < items[0]) {
        right--;
    }
    while (left < right) {
        // exchange the positions
        temp_pos = positions[left];
        positions[left] = positions[right];
        positions[right] = temp_pos;
        
        // exchange the value
        temp = items[left];
        items[left] = items[right];
        items[right] = temp;
        
        while(left < right && items[left] >= items[0]) {
            left++;
        }
        while(items[right] < items[0]) {
            right--;
        }
    }
    
    // Putting the pivot element in the right position
    temp_pos = positions[0];
    positions[0] = positions[right];
    positions[right] = temp_pos;
    
    temp = items[0];
    items[0] = items[right];
    items[right] = temp;
    
    track_sort_items(items, right, positions);
    track_sort_items(items + right + 1, n - right - 1, positions + right + 1);
}

unsigned int *alloc_positions(unsigned int n)
{
    unsigned int *result = malloc(sizeof(unsigned int) * n);
    unsigned int i = 0;
    while (i < n) {
        result[i] = i;
        i++;
    }
    return result;
}

uint_matrix *matrix_from_items(double items[], unsigned int n, unsigned int limit){
    if( n == 0 ){
        return alloc_uint_matrix(n,0);
    }
    unsigned int *store;
    unsigned int m = 0;
    unsigned int size = n * n;// we will at least have n rows and n columns
    unsigned int colsize = sizeof(unsigned int) * n;
    unsigned int *max = malloc(colsize);
    unsigned int *col = malloc(colsize);
    unsigned int i = 0, j = 0;
    unsigned int max_items;
    unsigned int cur_items = 0;
    double fill = 0;
    double min;
    unsigned int min_pos =0;
    double min_fill;
    uint_matrix *matrix;

    // items must be sorted
    for( i=1; i<n; i++ ){
        assert(items[i-1] >= items[i]);
    }
    i = 0;

    min = items[0];
    while( i < n ){
        max[i] = floor(PACKING_SIZE / items[i]);
        if( max[i] > limit ){
            max[i] = limit;
        }
        if( min > items[i] ){
            min = items[i];
            min_pos = i;
        }
        i++;
    }

    max_items = floor(PACKING_SIZE / min);

    memset(col, 0, colsize);

    min_fill = PACKING_SIZE - min;

    store = malloc(size * sizeof(unsigned int) );

    // TODO: this is fucking close to brute force!
    while( 1 ){
        i = 0;
        while( i < n ){
            col[i]++;
            cur_items++;
            fill = 0;
            for( j = 0 ; j < n ; j++ ){
                fill += items[j] * col[j];
            }
            if( fill > PACKING_SIZE || col[i] > max[i] || cur_items > max_items ){
                cur_items -= col[i];
                col[i] = 0;
            }else{
                break;
            }
            i++;
        }
        if( i == n ){
            break ;
        }
        char valid = 1;
        for( j=n; j > 0 ; j-- ){
            if( (fill + items[j-1]) <= PACKING_SIZE ){
                if( col[j-1] < max[j-1] ){
                    // this item could have been put into the bin
                    valid = 0;
                    break;
                }
            }else{
                // too big
                break;
            }
        }
        if( valid ){
            // this configuration is valid
            if( (m + 1)*n >= size ){
                size *= 2;
                store = realloc(store, size * sizeof(unsigned int));
            }
            memcpy( store + ( m * n ), col, colsize );
            m++;
        }
    }

    matrix = alloc_uint_matrix(m, n);
    memcpy(matrix->values, store, m * n * sizeof(unsigned int));
    free(store);
    free(max);
    free(col);
    return matrix;
}

