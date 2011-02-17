/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include "packing_list.h"
#include "first_fit.h"

packing_list * first_fit(double items[], unsigned int n){
    unsigned int i = 0;
    packing_list * result = alloc_packing_list();
    if( n == 0 ){
        // puh, this was heavy
        return result;
    }
    while( i < n ){
        first_fit_step(items, n, i, result );
        i++;
    }
    return result;
}

void first_fit_step(double items[], unsigned int n, item_number item,packing_list * result){
    packing_container * cont = result->list;
    packing * pack;
    double item_size = items[item];
    while( cont ){
        if( packing_has_room_for(cont->value, items, item_size) ){
            // this will fit in here
            if( cont->quantity == 1 ){
                // modify this packing
                //TODO: maybe the resulting packing is already present in the packing_list
                insert_item(cont->value,item);
            }else{
                // take one packing and reinsert a clone
                cont->quantity--;
                pack = clone_packing(cont->value);
                insert_item(pack,item);
                insert_packing(result, pack, 1);
            }
            return ;
        }
        cont = cont->next;
    }
    // the item didn't fit anywhere
    pack = alloc_packing();
    insert_item(pack, item);
    insert_packing(result, pack, 1);
}
