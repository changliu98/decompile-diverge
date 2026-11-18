#include <stdio.h>

void exchange (int * const pint1, int * const pint2)
{
    int temp;
    temp = *pint1;
    *pint1 = *pint2;
    *pint2 = temp;
}
