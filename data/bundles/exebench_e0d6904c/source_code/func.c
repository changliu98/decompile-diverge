#include <stdio.h>

#include <time.h>

static inline void swap(int *a, int *b)
{
 int t;
 t = *a;
 *a = *b;
 *b = t;
}
