#include <stdio.h>

#include <stdlib.h>

#include <string.h>

char* str_rev(char* s)
{
    char* h = s;
    char* t = s;
    char ch;
    while(*t++){};
    t--;
    t--;
    while(h < t)
    {
        ch = *h;
        *h++ = *t;
        *t-- = ch;
    }
    return (s);
}
