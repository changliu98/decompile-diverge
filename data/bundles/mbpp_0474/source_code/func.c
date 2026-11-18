

#include <stdio.h>

#include <string.h>

#include <assert.h>



char* func0(char* str1, char ch, char newch) {
  static char str2[100];
  strcpy(str2, str1);
  for (int i = 0; i < strlen(str2); i++) {
    if (str2[i] == ch) {
      str2[i] = newch;
    }
  }
  return str2;
}
