#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <assert.h>



char* func0(const char* str1, char* result) {
  int j = 0;
  for (int i = 0; i < strlen(str1); i++) {
    if (!isspace(str1[i])) {
      result[j++] = str1[i];
    }
  }
  result[j] = '\0';
  return result;
}
