#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <errno.h>

static char *trim(char *str, char *trim_chars)
{
    char *endstr;

    if(!str)
        return str;

    endstr = index(str, 0) - 1;

    while(endstr >= str && index(trim_chars, *endstr))
    {
        *endstr = 0;
        endstr--;
    }

    return str;
}
