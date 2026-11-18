

#include <stdio.h>

#include <assert.h>

#include <string.h>



int func0(const char *str1, const char *str2) {
  int count = 0;
  int len = strlen(str1);
  for (int i = 0; i < len; i++) {
    if (str1[i] != str2[i]) {
      count++;
    }
  }
  if (count % 2 == 0) {
    return count / 2;
  } else {
    return -1;
  }
}
