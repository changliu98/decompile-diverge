#include <setjmp.h>

#include <stdlib.h>

#include <unistd.h>

int increase_1 (int *a)
{
  *a += 1;
  return -5;
}
