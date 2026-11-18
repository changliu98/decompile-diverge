#include <stdio.h>

double readDummyArray (double *dummy, unsigned long sizeMB)
{
    unsigned long end = sizeMB / sizeof (*dummy), i;
    double a = 0;

    for (i = 0 ; i < end ; i++)
    {
        a += dummy[i];
 }

    dummy[0] = a/end;

    return a;
}
