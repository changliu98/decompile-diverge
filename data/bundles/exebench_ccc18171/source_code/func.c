#include <stdio.h>

#include <stdlib.h>

int ok_smul4(int x, int y, int *dest)
{
    unsigned char byte_result;

    *dest = x*y;




    asm("setae %0"
 : "=r" (byte_result)
 );

    return (int) byte_result;
}
