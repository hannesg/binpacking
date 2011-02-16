/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#include "solution.h"

packing_list * new_packing_list(packing * pack, packing_list * next = NULL){
	packing_list * result = malloc(sizeof(packing_list));
	result->value = pack;
	result->next = next;
	return result;
}

void free_packing_container(packing_container * list){
	if( list != NULL ){
		free_packing_container(list->next);
		free_packing(list->value);
		free(list);
	}
}

packing * new_packing(){
	packing * pack = malloc(sizeof(packing));
	pack->size = 0;
	pack->items = NULL;
	return pack;
}

void free_packing(packing * pack){
	free(pack->items);
	free(pack);
}

unsigned int packing_contains(packing *pack, item_number item){
	for( unsigned int i=0; i < pack->size; i++ ){
        if( pack->items[i] == item ){
            return 1;
        }
    }
    return 0;
}

void prepend_packing(solution * sol, packing * pack){
	sol->list = new_packing_container(pack, sol->list);
	sol->size++;
}

