/*
 * knapsack.c
 *
 *  Created on: Mar 17, 2011
 *      Author: hannes
 */

#include "knapsack.h"
#include <errno.h>

uint_vector *bound_knapsack( uint_vector *sizes,
                             uint_vector *profits,
                             unsigned int B,
                             unsigned int limit){
    assert( sizes->size == profits->size );
    assert( sizes->size > 0 );
    unsigned int n = sizes->size;
    unsigned int **minSizes;
    unsigned int ***minSizeConfigurations;
    int profit;
    unsigned int minSize = 0;

    unsigned int i=0;
    unsigned int j, l, size;

    unsigned int minSizeOverflow = 0;
    unsigned int lastValidConfiguration;
    unsigned int maxProfit;

    unsigned int finalMinSize;
    unsigned int *finalMinSizeConfiguration;
    unsigned int finalMinSizeL;

    unsigned int allocated = n;

    unsigned int *emptyConfiguration = calloc(n, sizeof(unsigned int));

    maxProfit = profits->values[0];
    for( j = 1 ; j < n ; j++ ){
        if( profits->values[j] > maxProfit ){
            maxProfit = profits->values[j];
        }
    }

    /*
     * Initialize configuration with zero size.
     */
    minSizes = malloc(sizeof(void *) * allocated);
    minSizes[0] = calloc(sizeof(unsigned int), n);
    minSizeConfigurations = malloc(sizeof(void *) * allocated);
    minSizeConfigurations[0] = calloc(sizeof(void *), n);
    for( j = 0; j < n ; j++ ){
        minSizeConfigurations[0][j] = calloc(sizeof(unsigned int), n);
    }

    do{

        i++;

        if( allocated <= i ){
            allocated *= 2;
            minSizes = realloc(minSizes, sizeof(void *)*allocated);
            minSizeConfigurations = realloc(minSizeConfigurations, sizeof(void *)*allocated);
        }
        minSizes[i] = calloc( n , sizeof(unsigned int) );
        minSizeConfigurations[i] = calloc( n , sizeof(unsigned int *) );

        // j = 0 is special, since it can be easily calculated directly
        div_t d = div( i , profits->values[0] );
        if( d.rem > 0 ){
            d.quot++;
        }
        if( d.quot > limit || d.quot*sizes->values[0] > B ){
            minSizes[i][0] = B + 1;
        }else{
            minSizes[i][0] = d.quot * sizes->values[0];
            minSizeConfigurations[i][0] = calloc( n , sizeof(unsigned int) );
            minSizeConfigurations[i][0][0] = d.quot;
        }

        // all other cases
        for( j = 1 ; j < n ; j++ ){
            finalMinSize = B + 1;
            finalMinSizeConfiguration = NULL;
            finalMinSizeL = 0;

            for( l = 0 ; l <= limit ; l++ ){
                profit = i - l * profits->values[j];
                if( profit > 0 ){
                    size = ( minSizes[profit][j-1] + l*sizes->values[j] );
                    if( size < finalMinSize &&
                        minSizeConfigurations[profit][j-1] != NULL
                        ){
                        finalMinSizeConfiguration = minSizeConfigurations[profit][j-1];
                        finalMinSizeL = l;
                        finalMinSize = size;
                    }
                }else if( profit == 0 ){
                    size = l * sizes->values[j];
                    if( size < finalMinSize ){
                        finalMinSizeConfiguration = emptyConfiguration;
                        finalMinSizeL = l;
                        finalMinSize = size;
                    }
                    break ;
                }else{
                    break ;
                }
            }
            if( finalMinSizeConfiguration ){
                minSizeConfigurations[i][j] = malloc( n * sizeof(unsigned int) );
                memcpy( minSizeConfigurations[i][j] , finalMinSizeConfiguration, n * sizeof(unsigned int));
                minSizeConfigurations[i][j][j] = finalMinSizeL;
            }
            minSizes[i][j] = finalMinSize;
        }

        if( minSizes[i][n-1] > B ){
            minSizeOverflow++;
        }else{
            lastValidConfiguration = i;
            minSizeOverflow = 0;
        }

    }while( minSizeOverflow <= maxProfit );

    // create result
    minSize = B + 1;
    unsigned int minSizePosition = n;
    for( j = 0 ; j < n ; j++ ){
        if( minSize > minSizes[lastValidConfiguration][j] ){
            minSizePosition = j;
            minSize = minSizes[lastValidConfiguration][j];
        }
    }
    assert( minSizePosition < n );

    uint_vector *result = alloc_uint_vector(n);
    memcpy( result->values , minSizeConfigurations[lastValidConfiguration][minSizePosition], sizeof(unsigned int)*n );

    // clean memory
    for( l = 0 ; l < i ; l++ ){
        free(minSizes[l]);
        for( j = 0 ; j < n ; j++ ){
            free(minSizeConfigurations[l][j]);
        }
        free(minSizeConfigurations[l]);
    }
    free(minSizes);
    free(minSizeConfigurations);

    return result;
}

uint_vector *approximate_bound_knapsack( uint_vector *sizes,
                                         uint_vector *profits,
                                         unsigned int knapsack_size,
                                         unsigned int limit,
                                         double precision ){

}
