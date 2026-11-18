#include <ctype.h>

#include <errno.h>

#include <stdbool.h>

#include <stdint.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

void
jsonny_clear(char *s, size_t *len) {
  *len = 0;
  s[0] = '\0';
}
