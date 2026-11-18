#include <stdio.h>

int summe(int *n, int *s)
{
  return ((*n == 0) || (*s += *n, (*n)--, summe(n, s)));
}
