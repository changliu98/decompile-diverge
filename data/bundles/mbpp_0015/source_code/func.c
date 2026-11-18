

#include <assert.h>

#include <ctype.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>



char** func0(const char* text, int* count) {
  char** result = NULL;
  *count = 0;
  int len = strlen(text);
  int i = 0;
  while (i < len) {
    if (islower((unsigned char)text[i])) {
      int start = i;
      i++;
      while (i < len && !islower((unsigned char)text[i])) {
        i++;
      }
      int end = i;
      int substr_len = end - start;
      char* substr = (char*)malloc(substr_len + 1);
      strncpy(substr, text + start, substr_len);
      substr[substr_len] = '\0';
      result = (char**)realloc(result, sizeof(char*) * (*count + 1));
      result[*count] = substr;
      (*count)++;
    } else {
      i++;
    }
  }
  return result;
}
