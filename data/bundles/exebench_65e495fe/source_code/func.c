#include <string.h>

#include <strings.h>

#include <ctype.h>

#include <sys/types.h>

#include <stdarg.h>

#include <stdlib.h>

#include <stdio.h>

static void dopr_outch(char *buffer, size_t *currlen, size_t maxlen, char c)
{
 if (*currlen < maxlen) {
  buffer[(*currlen)] = c;
 }
 (*currlen)++;
}
