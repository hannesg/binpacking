/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

// Standard
#include <stdlib.h>

// Library
#include "double_vector.h"
#include "parse_instance.h"
#include "binpacking.h"

int main(int argc, char **argv) {
    if(argc > 1) {
        double precision = 0.25;
        BinpackingAlgorithm algorithm = Good;
        int handle_large_item_seperately = 1;
        double_vector *instance = NULL;
        
        int i;
        for(i = 1; i < argc; ++i) {
            if(strcmp(argv[i], "--good") == 0) {
                algorithm = Good;
            }
            else if(strcmp(argv[i], "--bad") == 0) {
                algorithm = Bad;
            }
            else if(strcmp(argv[i], "--ugly") == 0) {
                algorithm = Ugly;
            }
            else if(strcmp(argv[i], "--do-not-handle-large-items-seperately") == 0) {
                handle_large_item_seperately = 0;
            }
            else if(strcmp(argv[i], "--handle-large-items-seperately") == 0) {
                handle_large_item_seperately = 1;
            }
            else if(strcmp(argv[i], "--precision") == 0) {
                if(i + 1 < argc) {
                    precision = atof(argv[i+1]);
                    printf("Value for precision is %s\n", argv[i+1]);
                    if(precision >= 1.0 || precision <= 0.0) {
                        printf("The precision has to be between 0 and 1.\n");
                        return 1;
                    }
                    printf("Precision is now %lf\n", precision);
                    ++i;
                }
                else {
                    printf("After '--precision' a float value has to follow.\n");
                    return 1;
                }
            } else {
                instance = parse_instance(argv[i]);
                if(!instance) {
                    printf("Please provide a valid filename.\n");
                    return 1;
                }
            }
        }
        
        if(instance) {
            packing_list *result = binpacking(instance->values,
                                              precision,
                                              instance->size,
                                              algorithm,
                                              handle_large_item_seperately);
            if(result == NULL) {
                printf("No solution found.");
            }
            else {
                printf("%i bins will be needed.\n", result->size);
                printf("The calculated packing for precision = %lf is:\n", precision);
                print_packing_list(result);
                free_packing_list(result);
            }
            
            free_double_vector(instance);
        }
    }
    return 0;
}
