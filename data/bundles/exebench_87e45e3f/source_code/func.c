#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

static void
encode_int( char *c, int i )
{
    int negative = 0;

    if ( i > 0 )
    {
        if ( i & 0x7C00 )
            *c++ = ( ( i >> 10 ) & 0x1F ) | 0x40;
        if ( i & 0x03F0 )
            *c++ = ( ( i >> 4 ) & 0x3F ) | 0x40;
    }
    else
    {
        i = -i;
        negative = 1;
    }

    if ( i & 0x000F )
        *c = ( i & 0x0F ) | 0x20;
    else
        *c = 0x20;

    if ( !negative )
        *c |= 0x10;

    c++; *c = '\0';
    return;
}
