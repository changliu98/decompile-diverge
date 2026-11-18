

#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include <stdlib.h>

#include <assert.h>



char* func0(const char* str1) {
  size_t len = strlen(str1);
  char* result = malloc(len + 1);
  if (!result) return NULL;
  if (len > 0) {
    result[0] = toupper(str1[0]);
    for (size_t i = 1; i < len; i++) {
      result[i] = tolower(str1[i]);
    }
    result[len - 1] = toupper(result[len - 1]);
    result[len] = '\0';
  }
  return result;
}
