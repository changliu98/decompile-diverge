#include <stdio.h>

#include <stdlib.h>

#include <math.h>

void swap(int *k, int *i)
{
  int zero_buffer;
  zero_buffer = *k;
  *k=*i;
  *i=zero_buffer;
}
