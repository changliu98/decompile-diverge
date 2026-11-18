#include <stdio.h>

#include <stdlib.h>

#include <string.h>

void conv_sign( unsigned int sign_bit, int *value )
{
    if( *value & sign_bit )
    {
        *value = (sign_bit << 1) - *value;
        *value *= -1;
    }
}
