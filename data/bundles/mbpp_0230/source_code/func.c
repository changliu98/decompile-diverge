

#include <stdio.h>

#include <string.h>

#include <assert.h>



char* func0(const char* str1, char* char_replacement) {
  static char str2[100];
  int j = 0;
  for (int i = 0; str1[i] != '\0'; i++) {
    if (str1[i] == ' ') {
      str2[j++] = char_replacement[0];
    } else {
      str2[j++] = str1[i];
    }
  }
  str2[j] = '\0';
  return str2;
}
