#include <stdio.h>

#include <stdlib.h>

#include <string.h>

unsigned int parse_int(char *str, int *num) {
 int i = 0, minus_fl, digit, length, t = 1;
 char null = '\0';

 (*num) = 0;
 minus_fl = str[i] == '-';

 if(minus_fl)
  i++;

 for(length = 1; str[length] != null; length++)
  t = t * 10;

 for(; str[i] != null; i++) {
  digit = str[i] - 48;

  if((digit >= 0) & (digit <= 9)) {
   if(i > 0)
    t = t / 10;

   (*num) += t * digit;
  } else {
   num = 0;

   return 0;
  }
 }

 if(minus_fl)
  (*num) *= -1;

 return 1;
}
