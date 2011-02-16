/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#define INIT_SOLUTION(solution) \
	solution.size = 0; \
	solution.list = NULL;

typedef struct {
    unsigned int *items;
    unsigned int size;
} packing;

typedef struct _packing_container packing_container;

struct _packing_container {
    packing *value;
    packing_container *next;
};

typedef struct {
    unsigned int size;
    packing_container *list;
} packing_list;

packing_container * alloc_packing_container(packing * pack, packing_container * next);

void free_packing_container(packing_container * list);

void prepend_packing(packing_list * sol, packing * pack);

void free_packing(packing * pack);

