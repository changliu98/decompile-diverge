#include <stdlib.h>

#include <stdio.h>

void endian_swap32bit(unsigned int* x)
{
    *x = (*x>>24) |
        ((*x<<8) & 0x00FF0000) |
        ((*x>>8) & 0x0000FF00) |
        (*x<<24);
}
