#include <ctype.h>

#include <errno.h>

#include <fcntl.h>

#include <setjmp.h>

#include <stdint.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <unistd.h>

int putdword(char *p,int w)
{
    *p = w; *(p+1) = w >> 8;
    return (w);
}
