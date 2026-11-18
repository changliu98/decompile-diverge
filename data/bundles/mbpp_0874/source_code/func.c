

#include <assert.h>

#include <string.h>

#include <stdbool.h>



bool func0(const char* str1, const char* str2) {
  int N = strlen(str1);
  int M = strlen(str2);
  if (N % M != 0) {
    return false;
  }
  for (int i = 0; i < N; i++) {
    if (str1[i] != str2[i % M]) {
      return false;
    }
  }
  return true;
}
