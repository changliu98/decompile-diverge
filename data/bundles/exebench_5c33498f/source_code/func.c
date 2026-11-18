#include <stdio.h>

int error(int *x)
{
 *x=*x+1;
 return *x;
}
