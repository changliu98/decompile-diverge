#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <unistd.h>	

static int
endGCGdata(char *s, int *addend)
{
  *addend = 0;
  return (*s == '>');
}
