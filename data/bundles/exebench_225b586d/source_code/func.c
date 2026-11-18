#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <unistd.h>	

static int
endPearson(char *s, int *addend)
{
  *addend = 0;
  return(*s == '>');
}
