#include <ctype.h>

#include <float.h>

#include <math.h>

#include <regex.h>

#include <stddef.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

void reverse (char * s) {
 unsigned e, max;
 char tmp;

 for (e = 0; s[e] != '\0'; ++e);
 max = e;



 for (e = 0; e < max / 2; ++e) {
  tmp = s[e];
  s[e] = s[max - (e + 1)];
  s[max - (e + 1)] = tmp;
 }
}
