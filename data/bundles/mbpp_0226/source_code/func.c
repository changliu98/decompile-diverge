

#include <stdio.h>

#include <assert.h>

#include <string.h>



char* func0(char* str) {
  static char result[100];
  int j = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (i % 2 == 0) {
      result[j++] = str[i];
    }
  }
  result[j] = '\0';
  return result;
}
