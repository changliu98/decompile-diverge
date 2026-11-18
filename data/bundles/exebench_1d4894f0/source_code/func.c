#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <stdarg.h>

#include <limits.h>

static void stack4_replace_top(unsigned long *s, unsigned long e)
{
 *s = (*s & ~0xf) | e;
}
