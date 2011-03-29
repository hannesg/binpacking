/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Standard
#include <assert.h>

// Project
#include "uint_vector.h"
#include "double_vector.h"
#include "uint_matrix.h"

// Self
#include "binpacking.h"

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
     * The partition starts.
     */
    unsigned int *partition_starts;

    /*
     * Items smaller than delta will be ignored first and will be inserted later using first fit.
     */
    double delta = epsilon / 2;

    /*
     * Smalles i with items[i] < delta.
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
    // TODO: Possible speed enhancement with binary search.
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

    k = ceil((delta * delta * min_small_n)/2);
    // k > 0 since min_small_n > 1
    // TODO: If k == 1 we will win nothing by partitioning the items. Fallback?
    m = ceil((double) min_small_n/(double) k);

    // create the partitions
    // TODO: Do we always need m partitions? Maybe we need only m-1.
    partition_items = malloc(m * sizeof(double));
    partition_sizes = malloc(m * sizeof(unsigned int));
    partition_starts = malloc(m * sizeof(unsigned int));

    for(i = 0; i < m; i++) {
        unsigned int partition_start = i * k;
        unsigned int partition_size = min_small_n - partition_start;

        if(partition_size > k) {
            partition_size = k;
        }

        partition_starts[i] = partition_start;
        partition_items[i] = items[ partition_start ];
        partition_sizes[i] = partition_size;
    }

    // this matrix contains all possible packings
    A = matrix_from_items(partition_items + 1, m - 1, k);

    b = alloc_uint_vector(m - 1);
    fill_uint_vector(b, k);

    // solve the LP approximately
    double area = 0.0;
    for(i = 1; i < m - 1; ++i) {
        area += partition_sizes[i];
    }
    area *= k;
    x = approximate_lp_solver(A, b, delta, ceil(area), ceil(2 * area + 1));
    
    if(x == NULL) {
        // approximate_lp_solver did not find a solution

        free(items);
        free(partition_items);
        free(partition_sizes);
        free(partition_starts);
        free(positions);

        free_uint_vector(b);
        free_uint_matrix(A);

        return NULL;
    }
    // dummy:
//     x = alloc_double_vector(A->width);

    // pack the solutions
    result = alloc_packing_list();
    uint_vector *order = double_vector_order(x);

    for(i = 0; i < order->size; i++) {
        int current_packing = order->values[i];
        for(g = ceil(x->values[current_packing]); g > 0; g--) {
            // generate packing
            pack = alloc_packing();
            int itemExists = 0;
            
            // First see, if we still have at least one of the items
            for(j = 0; j < m - 1; j++) {
                if(uint_matrix_elem(A, current_packing, j) > 0
                   && partition_sizes[j + 1] > 0)
                {
                    itemExists = 1;
                    break;
                }
            }
            
            if(!itemExists) {
                free_packing(pack);
                continue;
            }
            
            for(j = 0; j < m - 1; j++) {
                aij = uint_matrix_elem(A, current_packing, j);

                for(h = 0; h < aij; h++) {
                    // we pack the original items directly or a smaller one
                    // depending on whether we have already packed a bigger one
                    int substPartitionNr = j + 1;
                    while( substPartitionNr < m
                           && partition_sizes[substPartitionNr] <= 0
                           && substPartitionNr < m)
                    {
                        substPartitionNr++;
                    }
                    if(substPartitionNr < m) {
                        // we haven't packed all items in this partition
                        partition_sizes[substPartitionNr]--;
                        insert_item(pack, positions[partition_starts[substPartitionNr] + partition_sizes[substPartitionNr]]);
                    }
                }
            }
            if(pack->size == 0) {
                free_packing(pack);
            }
            else {
                insert_packing(result, pack, 1);
            }
        }
    }
    // assert: every partition_sizes == 0

    // pack the big items
    i = 0;
    while(i < k) {
        pack = alloc_packing();
        insert_item(pack, positions[i]);
        insert_packing(result, pack, 1);
        i++;
    }

    // pack the small items
    i = min_small_n;
    while(i < n) {
        first_fit_step(items_in, n, positions[i], result);
        i++;
    }

    // rewrite the positions in the solution
    // is now unnecessary
    //renumber_packing_list(result, positions);

    // free memory
    free_uint_matrix(A);
    free_uint_vector(b);
    free_uint_vector(order);
    free_double_vector(x);
    free(items);
    free(partition_items);
    free(partition_sizes);
    free(partition_starts);
    free(positions);

    // done!
    return result;
}

void track_sort_items(double items[], unsigned int n, unsigned int positions[])
{
    double temp;
    unsigned int left = 1, right = n - 1, temp_pos;
    if(n <= 1) {
        return;
    }
    
    while(left < right && items[left] >= items[0]) {
        left++;
    }
    while(items[right] < items[0]) {
        right--;
    }
    while(left < right) {
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
    while(i < n) {
        result[i] = i;
        i++;
    }
    return result;
}

uint_matrix *matrix_from_items(double items[], unsigned int n, unsigned int limit){
    if(n == 0){
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
    for(i=1; i<n; i++) {
        assert(items[i-1] >= items[i]);
    }
    i = 0;

    min = items[0];
    while(i < n) {
        max[i] = floor(PACKING_SIZE / items[i]);
        if(max[i] > limit) {
            max[i] = limit;
        }
        if(min > items[i]) {
            min = items[i];
            min_pos = i;
        }
        i++;
    }

    max_items = floor(PACKING_SIZE / min);

    memset(col, 0, colsize);

    min_fill = PACKING_SIZE - min;

    store = malloc(size * sizeof(unsigned int));

    // TODO: this is fucking close to brute force!
    while(1) {
        i = 0;
        while(i < n) {
            col[i]++;
            cur_items++;
            fill = 0;
            for(j = 0 ; j < n ; j++) {
                fill += items[j] * col[j];
            }
            if(fill > PACKING_SIZE || col[i] > max[i] || cur_items > max_items) {
                cur_items -= col[i];
                col[i] = 0;
            } else {
                break;
            }
            i++;
        }
        if(i == n) {
            break;
        }
        char valid = 1;
        for(j=n; j > 0; j--) {
            if((fill + items[j-1]) <= PACKING_SIZE) {
                if(col[j-1] < max[j-1]) {
                    // this item could have been put into the bin
                    valid = 0;
                    break;
                }
            } else {
                // too big
                break;
            }
        }
        if(valid) {
            // this configuration is valid
            if((m + 1)*n >= size) {
                size *= 2;
                store = realloc(store, size * sizeof(unsigned int));
            }
            memcpy(store + (m * n), col, colsize);
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

void print_partition(double *partition_sizes, unsigned int *partition_count, int size)
{
    int i;
    for(i = 0; i < size; ++i) {
        printf("Partition %3i, size %8.4lf, count %2u\n", i, partition_sizes[i], partition_count[i]);
    }
}

