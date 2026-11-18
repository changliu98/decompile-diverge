#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <unistd.h>	

static int
endGB(char *s, int *addend)
{
  *addend = 0;
  return ((strstr(s,"//") != NULL) || (strstr(s,"LOCUS") == s));
}
