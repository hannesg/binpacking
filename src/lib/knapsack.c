/*
 * knapsack.c
 *
 *  Created on: Mar 17, 2011
 *      Author: hannes
 */

#include "knapsack.h"

uint_vector *bound_knapsack( double_vector *sizes,
                             uint_vector *profits,
                             double B,
                             unsigned int limit){
    assert( sizes->size == profits->size );
    assert( sizes->size > 0 );
    assert( B > 0 );
    assert( B < INFINITY );
    unsigned int n = sizes->size;
    double **minSizes;
    unsigned int ***minSizeConfigurations;
    int profit;
    double minSize = 0;
    double tooBig = nextafter(B, INFINITY);

    unsigned int i=0;
    unsigned int j, l;
    double size;

    unsigned int minSizeOverflow = 0;
    unsigned int lastValidConfiguration;
    unsigned int maxProfit;

    double finalMinSize;
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
    minSizes[0] = calloc(sizeof(double), n);
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
        minSizes[i] = calloc( n , sizeof(double) );
        minSizeConfigurations[i] = calloc( n , sizeof(unsigned int *) );

        // j = 0 is special, since it can be easily calculated directly
        if( profits->values[0] == 0 ){
            // this is important, since scaling in the approximate version could produce profit-less items
            minSizes[i][0] = tooBig;
        }else{
            div_t d = div( i , profits->values[0] );
            if( d.rem > 0 ){
                d.quot++;
            }
            if( d.quot > limit || d.quot*sizes->values[0] > B ){
                minSizes[i][0] = tooBig;
            }else{
                minSizes[i][0] = d.quot * sizes->values[0];
                minSizeConfigurations[i][0] = calloc( n , sizeof(unsigned int) );
                minSizeConfigurations[i][0][0] = d.quot;
            }
        }

        // all other cases
        for( j = 1 ; j < n ; j++ ){
            finalMinSize = tooBig;
            finalMinSizeConfiguration = NULL;
            finalMinSizeL = 0;
            if( sizes->values[j]  == 0 ){
                if( minSizeConfigurations[i][j-1] != NULL ){
                    finalMinSizeConfiguration = minSizeConfigurations[i][j-1];
                    finalMinSize = minSizes[i][j-1];
                }
            }else{
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
    minSize = tooBig;
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
    for( l = 0 ; l <= i ; l++ ){
        free(minSizes[l]);
        for( j = 0 ; j < n ; j++ ){
            free(minSizeConfigurations[l][j]);
        }
        free(minSizeConfigurations[l]);
    }
    free(emptyConfiguration);
    free(minSizes);
    free(minSizeConfigurations);

    return result;
}

uint_vector *approximate_bound_knapsack( double_vector *sizes,
                                         double_vector *profits,
                                         double B,
                                         unsigned int limit,
                                         double precision ){
    assert( sizes->size == profits->size );
    assert( sizes->size > 0 );
    unsigned int n = sizes->size;
    unsigned int j;
    unsigned int maxProfit = profits->values[0];
    for( j = 1 ; j < n ; j++ ){
        if( profits->values[j] > maxProfit ){
            maxProfit = profits->values[j];
        }
    }
    unsigned int scale = floor(precision * (double)( maxProfit / n) );
    uint_vector *scaled_profits = alloc_uint_vector(n);
    if( scale <= 1 ){
        for( j = 0 ; j < n ; j++ ){
            scaled_profits->values[j] = floor(profits->values[j]);
        }
    }else{
        for( j = 0 ; j < n ; j++ ){
            scaled_profits->values[j] = floor(profits->values[j] / scale);
        }
    }

    uint_vector *result = bound_knapsack(sizes, scaled_profits, B, limit);

    free_uint_vector(scaled_profits);

    return result;
}
