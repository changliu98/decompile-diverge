#include <math.h> /* for log10() and floor() */

#include <stdio.h> /* for printf() */

const char * string_to_slong (const char *s, long *number)
{
  int sign, c = *s;
  do { if (c == '-') { sign = 1; c = *++s; } else if (c == '+') { sign = 0; c = *++s; } else sign = 0; } while (0);
  for (*number = 0; ((unsigned)(c - '0') <= (unsigned)('9' - '0')); *number = (((*number) << 1) + ((*number) << 3)) + (c - '0'), c = *++s);
  if (sign) *number = -*number;
  return s;
}
