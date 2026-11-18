#include <stdio.h>

#include <stdlib.h>

#include <string.h>

static char *unmakemask (int mask, char *smask) {
  int i = 0;
  if (mask & (1 << 0)) smask[i++] = 'c';
  if (mask & (1 << 1)) smask[i++] = 'r';
  if (mask & (1 << 2)) smask[i++] = 'l';
  smask[i] = '\0';
  return smask;
}
