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
    int cmp;
    if( !cont ){
        sol->list = new_packing_container(pack, quantity, sol->list);
        sol->size++;
        return ;
    }
    while( cont ){
        cmp = packing_cmp(cont->value, pack);
        if( cmp < 0 ){
// insert this here
            break;
        }else if( cmp == 0 ){
// already here
            cont->quantity += quantity;
            return ;
        }
        cont = cont->next;
    }
    cont->next = new_packing_container(pack, quantity, cont->next);
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
                if( aij ){
                    insert_item(pack,(item_number) aij);
                }
                j++;
            }
            insert_packing(&list, pack, x->values[i]);
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

