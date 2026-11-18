#include <stdio.h>

#include <stdlib.h>

int conv_hstring ( char *string, unsigned int * num)
{
int pos = 0;
*num = 0;

while (((string[pos] >= '0' && string[pos] <= '9') ||
       (string[pos] >= 'a' && string[pos] <= 'f')) && pos < 9) {
    if (string[pos] >= '0' && string[pos] <= '9')
        *num = (*num << 4) + ( string[pos++] - '0' );
    else
        *num = (*num << 4) + ( string[pos++] - 'a' ) + 10;
    }

return pos;
}
