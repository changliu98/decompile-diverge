

#include <stdio.h>

#include <string.h>

#include <assert.h>



int func0(char str[]) {
  int number_ctr = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      number_ctr += 1;
    }
  }
  return number_ctr;
}
