

#include <stdio.h>

#include <assert.h>

#include <string.h>



char* func0(int num) {
  static char roman_num[100];
  int val[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  char* syb[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                 "XL", "X",  "IX", "V",  "IV", "I"};
  roman_num[0] = '\0';
  int i = 0;
  while (num > 0) {
    while (num >= val[i]) {
      strcat(roman_num, syb[i]);
      num -= val[i];
    }
    i++;
  }
  return roman_num;
}
