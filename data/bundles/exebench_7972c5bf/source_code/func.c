#include <stdlib.h>

#include <string.h>

static void tagcpy (char *dest, char *src, int tag_size)
{
    char *s1 = src, *s2 = src + tag_size - 1;

    if (*s2 && !s2 [-1])
        s2--;

    while (s1 <= s2)
        if (*s1 == ' ')
            ++s1;
        else if (!*s2 || *s2 == ' ')
            --s2;
        else
            break;

    while (*s1 && s1 <= s2)
        *dest++ = *s1++;

    *dest = 0;
}
