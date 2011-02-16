/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include "packing_list.h"

packing_container * new_packing_container(packing * pack, packing_container * next ) {
    packing_container * result = malloc(sizeof(packing_container));
    result->value = pack;
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

void insert_item(packing *pack, item_number item ){
    pack->items = realloc(pack->items, sizeof(item_number) * (pack->size + 1));
    pack->items[pack->size] = item;
    pack->size++;
}

void prepend_packing(packing_list * sol, packing * pack ){
    sol->list = new_packing_container(pack, sol->list);
    sol->size++;
}
