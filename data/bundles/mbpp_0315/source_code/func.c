

#include <stdio.h>

#include <string.h>

#include <assert.h>



char* func0(const char* str) {
  int n = strlen(str);
  int i = 0;
  int currlen = 0;
  int maxlen = 0;
  int st = -1;
  static char result[100];
  while (i < n) {
    if (str[i] == ' ') {
      if (currlen % 2 == 0) {
        if (maxlen < currlen) {
          maxlen = currlen;
          st = i - currlen;
        }
      }
      currlen = 0;
    } else {
      currlen += 1;
    }
    i += 1;
  }
  if (currlen % 2 == 0) {
    if (maxlen < currlen) {
      maxlen = currlen;
      st = i - currlen;
    }
  }
  if (st == -1) {
    return "-1";
  }
  strncpy(result, str + st, maxlen);
  result[maxlen] = '\0';
  return result;
}
