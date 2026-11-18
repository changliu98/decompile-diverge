#include <unistd.h>

#include <stdio.h>

#include <math.h>

void
swap(int *pa, int *pb)
{
  int t;
  t=*pa; *pa=*pb; *pb=t;
}
