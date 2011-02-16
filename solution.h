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

typedef struct _packing_list packing_list;

struct _packing_list {
    packing *value;
    packing_list *next;
};

typedef struct {
    unsigned int size;
    packing_list *list;
} solution;

packing_list * new_packing_list(packing * pack, packing_list * next);

void prepend_packing(solution * sol, packing * pack);
