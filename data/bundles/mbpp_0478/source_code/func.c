

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <ctype.h>



char* func0(char* str1) {
  static char result[100];
  int i, j = 0;
  for (i = 0; str1[i] != '\0'; i++) {
    if (!islower(str1[i])) {
      result[j++] = str1[i];
    }
  }
  result[j] = '\0';
  return result;
}
