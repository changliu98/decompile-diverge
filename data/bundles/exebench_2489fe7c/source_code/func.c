#include <stdio.h>

#include <stdlib.h>

static void crc16_b(unsigned int *crc, unsigned char db)
{
    int i;

    for(i=0;i<8;i++) {
        *crc <<= 1;
        if((db^(*crc>>16)) & 1)
            *crc ^= 0x8005;
        db >>= 1;
    }
    *crc &= 0xFFFF;
}
