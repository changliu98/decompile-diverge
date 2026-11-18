#include <stdlib.h> /* malloc, free, strtol */

#include <string.h> /* memmove, strcmp */

#include <stdio.h>

static int runetochar(char *s, int c)
{
 if (c < 0x80) {
  s[0] = c;
  return 1;
 }
 if (c < 0x800) {
  s[0] = 0xC0 | (c >> 6);
  s[1] = 0x80 | (c & 0x3F);
  return 2;
 }
 if (c > 0x10FFFF)
  c = 0xFFFD;
 if (c < 0x1000) {
  s[0] = 0xE0 | (c >> 12);
  s[1] = 0x80 | ((c >> 6) & 0x3F);
  s[2] = 0x80 | (c & 0x3F);
  return 3;
 }
 s[0] = 0xf0 | (c >> 18);
 s[1] = 0x80 | ((c >> 12) & 0x3F);
 s[2] = 0x80 | ((c >> 6) & 0x3F);
 s[3] = 0x80 | (c & 0x3F);
 return 4;
}
