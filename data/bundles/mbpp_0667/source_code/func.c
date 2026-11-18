#include <stdio.h>

#include <assert.h>



int func0(const char *string, const char *vowels) {
  int count = 0;
  const char *s = string;
  const char *v;
  while (*s) {
    v = vowels;
    while (*v) {
      if (*s == *v) {
        count++;
        break;
      }
      v++;
    }
    s++;
  }
  return count;
}
