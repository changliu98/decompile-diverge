

#include <stdio.h>

#include <string.h>

#include <assert.h>



char* func0(const char* text) {
  static char result[100];
  strcpy(result, text);
  for (int i = 0; result[i] != '\0'; i++) {
    if (result[i] == ' ' || result[i] == ',' || result[i] == '.')
      result[i] = ':';
  }
  return result;
}
