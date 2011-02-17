/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include "binpacking.h"

packing_list * binpacking(double items[], double epsilon, unsigned int n){
// 1. extract small items
// 1.1 count small items

    //

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


