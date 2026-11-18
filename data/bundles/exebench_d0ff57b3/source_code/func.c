#include <stdio.h>

static void swap_1(int * a, int * b) {
 int c = *a;
 *a = *b;
 *b = c;
}
