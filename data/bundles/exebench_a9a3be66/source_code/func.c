#include <stdio.h>

#include <string.h>

#include <unistd.h>

void byte2bits(char c, char* s)
{
    int i = 7;
    while(i >= 0)
        *s++ = '0' + ((c >> i--)&0x1);
    *s = 0;
}
