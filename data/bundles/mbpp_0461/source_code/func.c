#include <assert.h>

#include <string.h>

#include <stdio.h>

int func0(const char *str) {
  int upper_ctr = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') upper_ctr += 1;
    return upper_ctr;
  }
}
