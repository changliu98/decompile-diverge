

#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <assert.h>

#include <stdlib.h>



char* func0(const char* text1) {
  size_t len = strlen(text1);
  char* result = (char*)malloc(len + 1);
  if (!result) return NULL;
  size_t j = 0;
  for (size_t i = 0; i < len; ++i) {
    if (isalnum((unsigned char)text1[i])) {
      result[j++] = text1[i];
    }
  }
  result[j] = '\0';
  return result;
}
