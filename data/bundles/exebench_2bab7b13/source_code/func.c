#include <stdio.h>

#include <stdlib.h>

void Swap8Bytes(char *bytes)
{
    char t;
    t = bytes[0]; bytes[0] = bytes[7]; bytes[7] = t;
    t = bytes[1]; bytes[1] = bytes[6]; bytes[6] = t;
    t = bytes[2]; bytes[2] = bytes[5]; bytes[5] = t;
    t = bytes[3]; bytes[3] = bytes[4]; bytes[4] = t;
}
