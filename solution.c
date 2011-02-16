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

void free_packing_list(packing_list * list){
	if( list != NULL ){
		free_packing_list(list->next);
		free_packing(list->value);
		free(list);
	}
}

void free_packing(packing * pack){
	free(pack->items);
	free(pack);
}

void prepend_packing(solution * sol, packing * pack){
	sol->list = new_packing_list(pack, sol->list);
	sol->size++;
}

