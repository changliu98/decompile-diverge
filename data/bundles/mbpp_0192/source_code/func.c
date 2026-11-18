

#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <assert.h>



int func0(const char *str) {
  int flag_l = 0;
  int flag_n = 0;
  while (*str) {
    if (isalpha((unsigned char)*str)) {
      flag_l = 1;
    }
    if (isdigit((unsigned char)*str)) {
      flag_n = 1;
    }
    str++;
  }
  return flag_l && flag_n;
}
