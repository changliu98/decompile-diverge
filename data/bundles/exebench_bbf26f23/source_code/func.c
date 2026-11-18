#include <string.h>

char* strcpy(char* dest, const char* src)
{
    unsigned int size = 0;
    while(src[size])
    {
        dest[size] = src[size];
        size++;
    }
    dest[size] = '\0';
    return dest;
}
