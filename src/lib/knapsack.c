/*
 * knapsack.c
 *
 *  Created on: Mar 17, 2011
 *      Author: hannes
 */

#include "knapsack.h"

uint_vector *bound_knapsack( uint_vector *sizes,
                             uint_vector *profits,
                             unsigned int B,
                             unsigned int limit){
    assert( sizes->size == profits->size );
    unsigned int n = sizes->size;
    unsigned int **minSizes;
    unsigned int ***minSizeConfigurations;
    int profit;
    unsigned int minSize = 0;

    unsigned int i=0;
    unsigned int j, l, size;

    /*
     * Initialize configuration with zero size.
     */
    minSizes = malloc(sizeof(void *));
    minSizes[0] = calloc(sizeof(unsigned int), n);
    minSizeConfigurations = malloc(sizeof(void *));
    minSizeConfigurations[0] = calloc(sizeof(void *), n);
    for( j = 0; j < n ; j++ ){
        minSizeConfigurations[0][j] = calloc(sizeof(unsigned int), n);
    }

    do{

        i++;

        // TODO: maybe we shouldn't realloc in *every* iteration
        minSizes = realloc(minSizes, sizeof(void *)*(i+1));
        minSizes[i] = calloc( n , sizeof(unsigned int) );
        minSizeConfigurations = realloc(minSizeConfigurations, sizeof(void *)*(i+1));
        minSizeConfigurations[i] = calloc( n , sizeof(unsigned int) );

        // j = 0 is special, since it can be easily calculated directly
        l = ceil( i / profits->values[0] );
        if( l > limit || l*sizes->values[0] > B ){
            minSizes[i][0] = B + 1;
            printf("can't reach %i with one item\n", i);
        }else{
            minSizes[i][0] = l * sizes->values[0];
            printf("reach %i with %i times one item size %i\n", i, l, minSizes[i][0]);
            minSizeConfigurations[i][0] = calloc( n , sizeof(unsigned int) );
            minSizeConfigurations[i][0][0] = l;
        }

        // all other cases
        for( j = 1 ; j < n ; j++ ){

            minSizes[i][j] = minSizes[i][j-1];
            if( minSizeConfigurations[i][j-1] ){
                minSizeConfigurations[i][j] = malloc(sizeof(unsigned int)*n);
                memcpy(minSizeConfigurations[i][j], minSizeConfigurations[i][j-1], sizeof(unsigned int)*n );
            }

            for( l = 0 ; l < limit ; l++ ){
                profit = i - l * profits->values[j];
                if( profit <= 0 ){
                    // for profit <= 0 the configuration is just empty
                    size = l*sizes->values[j];
                    if( size < minSizes[i][j] ){
                        minSizes[i][j] = size;
                        if( minSizeConfigurations[i][j] == NULL ){
                            minSizeConfigurations[i][j] = calloc( n , sizeof(unsigned int) );
                        }else{
                            memset( minSizeConfigurations[i][j] , 0 , sizeof(unsigned int)*n);
                        }
                        minSizeConfigurations[i][j][j]=l;
                    }
                }else{
                    size = l*sizes->values[j] + minSizes[profit][j-1];
                    if( size < minSizes[i][j] ){
                        minSizes[i][j] = size;
                        if( minSizeConfigurations[i][j] == NULL ){
                            minSizeConfigurations[i][j] = malloc(sizeof(unsigned int)*n);
                        }
                        if( minSizeConfigurations[profit][j] ){
                            memcpy( minSizeConfigurations[i][j] , minSizeConfigurations[profit][j-1] , sizeof(unsigned int)*n);
                            minSizeConfigurations[i][j][j]=l;
                            printf("found {%i, %i, %i} with %i using %i items\n", minSizeConfigurations[i][j][0], minSizeConfigurations[i][j][1], minSizeConfigurations[i][j][2], i, j);
                        }else{
                            printf("msc[%i]? msc[%i][%i] == NULL \n", i, profit, j);
                        }
                    }
                }
            }
        }
    }while( minSizes[i][n-1] <= B );

    // create result
    minSize = B + 1;
    unsigned int minSizePosition = n;
    for( j = 0 ; j < n ; j++ ){
        printf("[%i] = %i\n", j , minSizes[i-1][j] );
        if( minSize > minSizes[i-1][j] ){
            minSizePosition = j;
            minSize = minSizes[i-1][j];
        }
    }
    printf("i = %i\n",i);
    assert( minSizePosition < n );

    uint_vector *result = alloc_uint_vector(n);
    memcpy( result->values , minSizeConfigurations[i-1][minSizePosition], sizeof(unsigned int)*n );

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
