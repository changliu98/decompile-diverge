

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <stdlib.h>



char* func0(char* s, int d) {
  int len = strlen(s);
  char* tmp = (char*)malloc(len + 1);
  for (int i = 0; i < len; i++) {
    tmp[i] = s[(i + d) % len];
  }
  tmp[len] = '\0';
  return tmp;
}
