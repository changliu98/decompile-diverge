

#include <assert.h>

#include <string.h>



int func0(const char *str1) {
  int count_chars = 0;
  int length = strlen(str1);
  for (int i = 0; i < length; i++) {
    if ((i == (str1[i] - 'A')) || (i == (str1[i] - 'a'))) {
      count_chars += 1;
    }
  }
  return count_chars;
}
