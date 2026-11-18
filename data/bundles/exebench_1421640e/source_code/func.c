#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

static void
encode_vector( char *c, int x, int y )
{
    c[0] = ( y >> 5 ) + 0x20;
    c[1] = ( y & 0x1f ) + 0x60;
    c[2] = ( x >> 5 ) + 0x20;
    c[3] = ( x & 0x1f ) + 0x40;
    c[4] = '\0';
}
