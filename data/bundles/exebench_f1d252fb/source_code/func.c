#include <stdlib.h>

#include <stdio.h>

void endian_swap16bit(unsigned short* x)
{
    *x = (*x>>8) |
        (*x<<8);
}
