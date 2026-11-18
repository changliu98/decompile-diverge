#include <limits.h>

int swap(int *x, int *y) {
 int tmp = *x;
 *x = *y;
 *y = tmp;
 return 0;
}
