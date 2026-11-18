#include <stdio.h>

void Exchange(int *a, int *b) {
 int temp = *a;
 *a = *b;
 *b = temp;
}
