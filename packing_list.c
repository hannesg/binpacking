/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include "packing_list.h"

packing_container * new_packing_container(packing * pack, unsigned int quantity, packing_container * next ) {
    packing_container * result = malloc(sizeof(packing_container));
    result->value = pack;
    result->quantity = quantity;
    result->next = next;
    return result;
}

void free_packing_container(packing_container * list) {
    if (list != NULL) {
        free_packing_container(list->next);
        free_packing(list->value);
        free(list);
    }
}

packing * new_packing() {
    packing * pack = malloc(sizeof(packing));
    pack->size = 0;
    pack->items = NULL;
    return pack;
}

void free_packing(packing * pack) {
    free(pack->items);
    free(pack);
}

unsigned int packing_contains_item(packing *pack, item_number item) {
    unsigned int i = 0;
    while( i < pack->size ){
        if (pack->items[i] == item) {
            return 1;
        }
        i++;
    }
    return 0;
}

unsigned int packing_equals(packing *a, packing *b){
    if( a->size != b->size ){
        return 0;
    }else{
        return memcmp(a->items,b->items,a->size) == 0;
    }
}

void insert_item(packing *pack, item_number item ){
    item_number * items;
    unsigned int i = 0;
    if( pack->items ){
        items = pack->items;
        pack->items = malloc(sizeof(item_number) * (pack->size + 1));
        while( i < pack->size ){
            if( items[i] > item ){
                pack->items[i] = items[i];
            }else{
                pack->items[i] = item;
                memcpy(pack->items+i+1,items+i,pack->size-i);
                break;
            }
            i++;
        }
        free(items);
        pack->size++;
    }else{
        pack->items = malloc(sizeof(item_number));
        pack->items[0] = item;
        pack->size = 1;
    }
}

void prepend_packing(packing_list * sol, packing * pack , unsigned int quantity ){
    sol->list = new_packing_container(pack, quantity, sol->list);
    sol->size++;
}
