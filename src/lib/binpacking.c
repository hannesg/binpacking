/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

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
    double *partitioned_items;


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

    /**
     * The LP-Solution
     */
    double_vector *x;

    /*
     * We will use this positions later to generate a solution for J_LO.
     */
    unsigned int *partition_positions;

    /*
     * auxiliary variables
     */
    unsigned int h=0, i=0, j=0, aij;
    packing * pack;

    // copy and sort the given items
    memcpy(items, items_in, sizeof(double) * n);
    track_sort_items(items,n,positions);

    // determine the border between normal and small items
    while( min_small_n < n && items[min_small_n] >= delta ){
        min_small_n++;
    }

    if( min_small_n <= 1 ){
        // if max_normal_n == 0 then every item is small and we cannot partition the input.
        // if max_normal_n == 1 then k will be 0, which will result in empty partitions.
        //      => simply first fit them!
        //         since most are items are quite small, this will give acceptable results!
        free(positions);
        free(items);
        return first_fit(items_in, n);
    }

    k = ceil( (delta * delta * (min_small_n - 1) )/2 );
    // k > 0 since min_small_n > 1
    // TODO: If k == 1 we will win nothing by partitioning the items. Fallback?
    m = floor( (min_small_n - 1)/k );

    // create the partitions
    // TODO: Do we always need m partitions? Maybe we need only m-1.
    partitioned_items = malloc( m * sizeof(double) );
    partition_positions = malloc( m * sizeof(unsigned int) );
    i = 0;
    while( i < m ){
        partition_positions[i] = (i+1)*k + 1;
        partitioned_items[i] = items[ partition_positions[i]  ];
        i++;
    }

    // this matrix contains all possible packings
    A = matrix_from_items(partitioned_items, m, k);

    b = alloc_uint_vector(m);
    fill_uint_vector(b, k);

    // solve the LP approximately
    //x = approximate_lp_solver(A, b , delta);

    // pack the solutions
    i = 0;
    while( i < x->size ){
        if( x->values[i] > 0 ){
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
                        insert_item(pack, partition_positions[j]);
                        // this may exceed the partition, but this will make
                        // the solution only better
                        partition_positions[j]++;
                        h++;
                    }
                }
                j++;
            }
            insert_packing(result, pack, ceil(x->values[i]));
        }
        i++;
    }

    // pack the big items
    i = 0;
    while( i < k ){
        pack = alloc_packing();
        insert_item(pack, i);
        insert_packing(result, pack, 1);
        i++;
    }

    // pack the small items
    i = min_small_n;
    while( i < n ){
        first_fit_step(items, n, i, result);
    }

    // rewrite the positions in the solution
    // TODO: not necessary, if we pack positions[i] instead of i!
    renumber_packing_list(result, positions);

    // done!
    return result;
}

void track_sort_items(double items[], unsigned int n, unsigned int positions[])
{
    double temp;
    double pv;
    unsigned int i = 1, cut = 0, temp_pos;
    if (n <= 1) {
        return;
    }
    pv = items[0];
    while (i < n) {
        if (items[i] >= pv) {
            // this item should come before the cut
            // exchange the positions too
            temp_pos = positions[i];
            positions[i] = positions[cut];
            positions[cut] = temp_pos;
            // exchange the value
            temp = items[i];
            items[i] = items[cut];
            items[cut] = temp;

            cut++;
        }
        i++;
    }
    if( cut == 0 ){
        track_sort_items(items + 1, n - 1 , positions + 1);
    }else{
        track_sort_items(items, cut, positions);
        track_sort_items(items + cut, n - cut , positions + cut);
    }
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

void renumber_packing_list(packing_list * list, item_number * positions){
    packing_container * cont = list->list, * next = NULL;
    unsigned int size;
    packing * pack;
    item_number * items;
    unsigned int i;
    list->list = NULL;
    list->size = 0;
    while( cont ){
        next = cont->next;
        pack = alloc_packing();
        i = 0;
        size = cont->value->size;
        items = cont->value->items;
        while( i < size ){
            insert_item(pack, positions[items[i]]);
        }
        insert_packing(list, pack, cont->quantity );
        free_packing_container(cont);
        cont = next;
    }
}

uint_matrix *matrix_from_items(double items[], unsigned int n, unsigned int limit){
    unsigned int *store;
    unsigned int m = 0;
    unsigned int size = n * n;// we will at least have n rows and n columns
    unsigned int colsize = sizeof(unsigned int) * n;
    unsigned int *max = malloc(colsize);
    unsigned int *col = malloc(colsize);
    unsigned int i = 0, j = 0;
    unsigned int max_items;
    unsigned int cur_items = 0;
    double room;
    double min;
    double fill = 0;
    uint_matrix *matrix;

    min = items[0];
    while( i < n ){
        max[i] = floor(PACKING_SIZE / items[i]);
        if( max[i] > limit ){
            max[i] = limit;
        }
        if( min > items[i] ){
            min = items[i];
        }
        i++;
    }

    max_items = floor(PACKING_SIZE / min);

    memset(col, 0, colsize);

    store = malloc(size * sizeof(unsigned int) );

    // TODO: this is fucking close to brute force!
    while( 1 ){
        i = 0;
        while( i < n ){
            col[i]++;
            cur_items++;
            fill += items[i];
            if( fill > PACKING_SIZE || col[i] > max[i] ){
                fill -= col[i] * items[i];
                col[i] = 0;
            }else{
                break;
            }
            i++;
        }
        if( fill > 0 && (PACKING_SIZE - fill) <= min ){
            // this configuration is valid
            if( (m + 1)*n >= size ){
                size *= 2;
                store = realloc(store, size * sizeof(unsigned int));
            }
            memcpy( store + ( m * n ), col, colsize );
            m++;
        }
        if( i == n ){
            break ;
        }
    }

    matrix = alloc_uint_matrix(m, n);
    memcpy(matrix->values, store, m * n * sizeof(unsigned int));
    free(store);
    free(max);
    free(col);
    return matrix;
}

