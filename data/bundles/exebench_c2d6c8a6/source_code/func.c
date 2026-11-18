#include <stdio.h>

#include <stdlib.h>

#include <time.h>

static void swap(int *a,int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
