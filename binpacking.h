/******************************************************************************
 * Authors:
 * 2011 Bastian Holst <bastianholst@gmx.de>
 *****************************************************************************/

typedef struct {
    int *items;
} packing;

typedef struct _packing_list packing_list;

struct _packing_list {
    packing *value;
    packing_list *next;
};

typedef struct {
    int n;
    packing_list *list;
} solution;

solution binpacking(double items[], double epsilon, int n);
