#include <stdlib.h>

#include <string.h>

void
gsm_hex_from_byte( char* hex, int val )
{
    static const char hexdigits[] = "0123456789abcdef";

    hex[0] = hexdigits[(val >> 4) & 15];
    hex[1] = hexdigits[val & 15];
}
