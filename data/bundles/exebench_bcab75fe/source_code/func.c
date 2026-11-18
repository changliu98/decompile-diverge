#include <stdio.h>

#include <stdlib.h>

int ok_smul1(int x, int y, int *dest)
{
    int result = 0;

    *dest = x*y;
    asm("setae %al");
    return result;
}
