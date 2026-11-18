#include <stdio.h>

#include <stdint.h>

#include <inttypes.h>

void numconv(char* numstr)
{
        for( ; *numstr; *numstr++ -= '0')
                ;

        return;
}
