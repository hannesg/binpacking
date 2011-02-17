/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include "packing_list.h"
#include <stdio.h>

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

packing * alloc_packing() {
    packing * pack = malloc(sizeof(packing));
    pack->size = 0;
    pack->items = NULL;
    return pack;
}

void free_packing(packing * pack) {
    free(pack->items);
    free(pack);
}

packing * clone_packing(packing * pack){
    packing * result = malloc(sizeof(packing));
    size_t memsize = sizeof(item_number) * result->size;
    result->size = pack->size;
    result->items = malloc(memsize);
    memcpy(result->items, pack->items, memsize);
    return result;
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

int packing_cmp(packing *a, packing *b){
    if( a->size > b->size ){
        return 1;
    }else if( a->size < b->size ){
        return -1;
    }else{
        return memcmp(a->items,b->items,a->size);
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
                memcpy(pack->items+i+1,items+i,sizeof(item_number) * (pack->size-i));
                break;
            }
            i++;
        }
        if( i == pack->size ){
            pack->items[i] = item;
        }
        free(items);
        pack->size++;
    }else{
        pack->items = malloc(sizeof(item_number));
        pack->items[0] = item;
        pack->size = 1;
    }
}

void insert_packing(packing_list * sol, packing * pack , unsigned int quantity ){
    packing_container * cont = sol->list;
    packing_container * next = NULL;
    int cmp;
    if( !cont ){
        // empty list
        sol->list = new_packing_container(pack, quantity, sol->list);
        sol->size++;
        return ;
    }
    cmp = packing_cmp(cont->value, pack);
    if( cmp < 0 ){
        // this item will be packed in the first place
        sol->list = new_packing_container(pack, quantity, sol->list);
        sol->size++;
        return ;
    }
    next = cont->next;
    while( next ){
        cmp = packing_cmp(next->value, pack);
        if( cmp < 0 ){
// insert this here
            break;
        }else if( cmp == 0 ){
// already here
            next->quantity += quantity;
            return ;
        }
        cont = next;
        next = next->next;
    }
    cont->next = new_packing_container(pack, quantity, next);
    sol->size++;
    return ;
}

void print_packing(packing *pack){
    unsigned int i = 0;
    i = 0;
    while( i < pack->size ){
        printf("%i ", pack->items[i]);
        i++;
    }
}

double packing_content(packing *pack, double items[]){
    unsigned int i=0;
    double sum = 0;
    while( i < pack->size ){
        sum += items[pack->items[i]];
        i++;
    }
    return sum;
}

int packing_has_room_for(packing *pack, double items[], double item){
    unsigned int i=0;
    double sum = PACKING_SIZE;
    while( i < pack->size ){
        sum -= items[pack->items[i]];
        if( sum < item ){
            return 0;
        }
        i++;
    }
    return 1;
}



packing_list * alloc_packing_list(){
    packing_list *list = malloc(sizeof(packing_list));
    list->size = 0;
    list->list = NULL;
    return list;
}

void free_packing_list(packing_list * list){
    free_packing_container(list->list);
    free(list);
}

packing_list * packing_list_from_ilp(uint_matrix * A, uint_vector *x){
    packing_list *list=alloc_packing_list();
    packing *pack;
    unsigned int i=0, j=0, aij=0;
    while( i < x->size ){
        if( x->values[i] ){
            // this packing is used
            pack = alloc_packing();
            j = 0;
            while( j < A->height ){
                aij = A->values[i + j * A->width];
                while( aij ){
                    insert_item(pack,(item_number) j);
                    aij--;
                }
                j++;
            }
            insert_packing(list, pack, x->values[i]);
        }
        i++;
    }
    return list;
}

void print_packing_list(packing_list *list){
    packing_container *ct = list->list;
    while( ct ){
        printf("%ix :",ct->quantity);
        print_packing(ct->value);
        printf("\n");
        ct = ct->next;
    }
}

