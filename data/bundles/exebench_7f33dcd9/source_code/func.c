#include <stdio.h>

void intSwap(int *x, int *y)

{
  int temp = *x;
  *x = *y;
  *y = temp;
}
