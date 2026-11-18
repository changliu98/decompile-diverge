#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <fcntl.h>

void outfname(char *s)
{
        while (*s)
                s++;
        *--s = 's';

}
