#include <stdio.h>

int doit(int *x, int y)
{
 if ((*x)>y)
 { (*x) = y;
 return 1; }
 return 0;
}
