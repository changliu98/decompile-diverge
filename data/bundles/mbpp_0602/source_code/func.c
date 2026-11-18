

#include <stdio.h>

#include <assert.h>

#include <string.h>



char func0(char* str1) {
  int length = strlen(str1);
  for (int i = 0; i < length; i++) {
    char c = str1[i];
    int count = 0;
    for (int j = 0; j <= i; j++) {
      if (str1[j] == c) {
        count++;
      }
    }
    if (count > 1) {
      return c;
    }
  }
  return '0';
}
