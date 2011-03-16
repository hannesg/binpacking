/******************************************************************************
 * Authors:
 * 2011 Hannes Georg <hannes.georg@googlemail.com>
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

#ifndef PACKING_LIST_H_
#define PACKING_LIST_H_

#define PACKING_SIZE 1

// Standard
#include <malloc.h>
#include <string.h>

// Project
#include "types.h"

/** @file packing_list.h
 *  @brief Packings and Packing Lists
 */

typedef unsigned int item_number;

/** @brief A packing contains different items.
 *
 */
typedef struct packing {
    /** @brief A field of items.
     *
     * The items are ordered descending and can appear in any number.
     *
     */
    item_number *items;
    /** @brief The number of items in the field.
     */
    unsigned int size;
} packing;

typedef struct packing_container packing_container;

struct packing_container {
    /** @brief a packing
     *
     */
    packing *value;
    /** @brief the number this packing is used
     *
     */
    unsigned int quantity;
    packing_container *next;
};

/** @brief A list of packings with quantities.
 *
 */
typedef struct packing_list {
    /** @brief the number of different packings used in this packing list
     *
     */
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

packing * clone_packing(packing * pack);

/**
 * Inserts an item into a pack
 */
void insert_item(packing *pack, item_number item );

/**
 * Inserts an item n times into a pack
 */
void insert_items(packing *pack, item_number item , unsigned int n);

/**
 * Compares two packings.
 * Returns 0 if they are equal, < 0 if a has fewer items or items with lower number and > 0 else.
 */
int packing_cmp(packing *a, packing *b);

/**
 * Checks if a packing contains an item with a given number.
 * @param pack the packing in which the item is inserted
 * @param item the item to be inserted
 */
unsigned int packing_contains_item(packing *pack, item_number item);

/**
 * Returns the content of the packing
 * @param pack the packing
 * @param items the item sizes
 */
double packing_content(packing *pack, double items[]);

/**
 * Returns whether the item fits in the packing.
 * @param pack the packing
 * @param items the item sizes
 * @param the item for which to test
 */
int packing_has_room_for(packing *pack, double items[], double item);

void print_packing(packing *pack);

/*
 * Packing List
 */

packing_list * alloc_packing_list();

void free_packing_list(packing_list * list);

/** @brief Creates a packing list from an ILP-solution.
 *
 * @param A the matrix used in the ILP
 * @param x the ILP-solution
 * @return a packing list which is equivalent to A and x
 */
packing_list * packing_list_from_ilp(uint_matrix * A, uint_vector *x);

void print_packing_list(packing_list * list);

#endif
