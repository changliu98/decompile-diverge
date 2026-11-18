

#include <assert.h>

#include <string.h>



int func0(const char* str) {
  int str_len = strlen(str);
  return (str_len * (str_len + 1)) / 2;
}
