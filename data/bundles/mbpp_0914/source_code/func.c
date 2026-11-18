

#include <assert.h>

#include <stdbool.h>

#include <string.h>



bool func0(const char* s) {
  int length = strlen(s);
  for (int i = 0; i < length - 2; i++) {
    if (s[i] != s[i + 2]) {
      return false;
    }
  }
  if (s[0] == s[1]) {
    return false;
  }
  return true;
}
