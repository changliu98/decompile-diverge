

#include <assert.h>

#include <string.h>



int func0(const char *string, char c) {
  int count = 0;
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == c) {
      count++;
    }
  }
  return count;
}
