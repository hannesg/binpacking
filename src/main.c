/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include "parse_instance.h"
#include "binpacking.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    if(argc > 1) {
        double precision = 0.25;
        double_vector *instance;
        
        int i;
        for(i = 1; i < argc; ++i) {
            if(strcmp(argv[i], "--precision") == 0) {
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
            packing_list *result = binpacking(instance->values, precision, instance->size);
            
            free_double_vector(instance);
            free_packing_list(result);
        }
    }
    return 0;
}
