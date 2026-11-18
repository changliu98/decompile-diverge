

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <ctype.h>

char* func0(const char* test_str) {
  static char res[1024];
  char dig[1024];
  int i = 0, j = 0;
  for (int idx = 0; test_str[idx] != '\0'; idx++) {
    if (isdigit(test_str[idx])) {
      dig[j++] = test_str[idx];
    } else {
      res[i++] = test_str[idx];
    }
  }
  dig[j] = '\0';
  res[i] = '\0';
  strcat(res, dig);
  return res;
}
