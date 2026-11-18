#include <stdint.h>

#include <stddef.h>

#include <stdbool.h>

#include <stdarg.h>

#include <string.h>

#include <ctype.h>

static void _uc(char *buf)
{
 for ( ; *buf; buf++) {
  if (*buf >= 'a' && *buf <= 'z') {
   *buf += 'A' - 'a';
  }
 }
}
