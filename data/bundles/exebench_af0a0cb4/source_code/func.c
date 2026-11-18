#include <stdio.h>

#include <time.h>

#include <stdlib.h>

void vertausche(int *x, int *y)
{
  int ablage = *x;
  *x = *y;
  *y = ablage;
}
