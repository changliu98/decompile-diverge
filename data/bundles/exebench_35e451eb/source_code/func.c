#include <stdio.h>

void adjust_point(int *n)
{
  if (*n < 0) {
    *n = 0;
  } else if (*n > 100) {
    *n = 100;
  }
}
