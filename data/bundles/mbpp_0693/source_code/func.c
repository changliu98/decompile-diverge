

#include <assert.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>



char* func0(const char* text1) {
  if (text1 == NULL) {
    return NULL;
  }
  size_t len = strlen(text1);
  char* result = malloc(len + 1);
  if (result == NULL) {
    return NULL;
  }
  size_t i = 0, j = 0;
  int space_found = 0;
  while (text1[i] != '\0') {
    if (text1[i] != ' ') {
      result[j++] = text1[i];
      space_found = 0;
    } else {
      if (!space_found) {
        result[j++] = ' ';
        space_found = 1;
      }
    }
    i++;
  }
  result[j] = '\0';
  return result;
}
