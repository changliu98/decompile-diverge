#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <time.h>

#include <getopt.h>

#include <string.h>

void
easterj (int year, int *month, int *day)
{
  int a, b, c, d, e, f, g;

  a = year % 4;
  b = year % 7;
  c = year % 19;
  d = (19 * c + 15) % 30;
  e = (2 * a + 4 * b - d + 34) % 7;
  f = (d + e + 114) / 31;
  g = (d + e + 114) % 31;

  *month = f;
  *day = g + 1;
}
