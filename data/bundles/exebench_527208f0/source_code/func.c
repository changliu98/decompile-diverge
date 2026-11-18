#include <stdio.h>

void interchange(int *u, int *v)
{
 int temp;

 temp = *u;
 *u = *v;
 *v = temp;
}
