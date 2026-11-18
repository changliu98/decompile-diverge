

#include <assert.h>

#include <string.h>



char* func0(const char* str1) {
  static char str2[100];
  int j = 0;
  for (int i = 1; i <= strlen(str1); i++) {
    if (i % 2 != 0) {
      str2[j++] = str1[i - 1];
    }
  }
  str2[j] = '\0';
  return str2;
}
