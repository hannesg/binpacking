/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#include <malloc.h>
#include <string.h>

#define INIT_SOLUTION(solution) \
    solution.size = 0; \
    solution.list = NULL;

typedef unsigned int item_number;

typedef struct {
    item_number *items;
    unsigned int size;
} packing;

typedef struct _packing_container packing_container;

struct _packing_container {
    packing *value;
    unsigned int quantity;
    packing_container *next;
};

typedef struct {
    unsigned int size;
    packing_container *list;
} packing_list;

/*
 * Packing Container Stuff
 */

packing_container * alloc_packing_container(packing * pack, unsigned int quantity, packing_container * next );

void free_packing_container(packing_container * list);

/**
 * Inserts @p quantity of @p pack into @p list.
 */
void insert_packing(packing_list * list, packing * pack, unsigned int quantity);

/*
 * Packing Stuff
 */

packing * alloc_packing();

void free_packing(packing * pack);

/**
 * Compares two packings.
 * Returns 0 if they are equal, < 0 if a has fewer items or items with lower number and > 0 else.
 */
int packing_cmp(packing *a, packing *b);

/**
 * Checks if a packing contains an item with a given number.
 */
unsigned int packing_contains_item(packing *pack, item_number item);

void print_packing(packing *pack);
