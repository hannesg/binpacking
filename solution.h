/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 *****************************************************************************/

#define INIT_SOLUTION(solution) \
	solution.size = 0; \
	solution.list = NULL;

#define FREE_SOLUTION(solution) \
	free_packing_list(solution.list);

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
} solution;

packing_list * new_packing_container(packing * pack, packing_container * next);

void free_packing_container(packing_container * list);

void prepend_packing(solution * sol, packing * pack);

void free_packing(packing * pack);

