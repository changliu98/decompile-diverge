#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <time.h>

#include <getopt.h>

#include <string.h>

void
eastero (int year, int *month, int *day)
{
  int a, b, c, d, e;

  a = year % 19;
  b = (19 * a + 15) % 30;
  c = (year + year / 4 + b) % 7;
  d = 10;
  if (year > 1600)
    d += year / 100 - 16 - (year / 100 - 16) / 4;
  e = b - c + d;

  *month = 3 + (e + 26) / 30;
  *day = 1 + (e + 27 + (e + 6) / 40) % 31;
}
