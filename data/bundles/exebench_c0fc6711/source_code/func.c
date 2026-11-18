#include <assert.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

void _quadtree_sort_swap(unsigned int *a, unsigned int *b) {
    unsigned int c;
    c = *a;
    *a = *b;
    *b = c;
}
