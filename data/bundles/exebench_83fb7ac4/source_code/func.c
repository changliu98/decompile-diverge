#include <assert.h>

#include <errno.h>

#include <math.h>

#include <stdarg.h>

#include <stdbool.h>

#include <stdlib.h>

#include <stdint.h>

#include <stdio.h>

#include <string.h>

#include <time.h>

char *stringCopy(char *s, const char *t)
{
        while ((*s = *t))
                s++, t++;
        return s;
}
