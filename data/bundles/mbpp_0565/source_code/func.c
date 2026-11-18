

#include <stdio.h>

#include <string.h>

#include <assert.h>



char* func0(char* word, char* result) {
  int length = strlen(word);
  for (int i = 0; i < length; i++) {
    result[i] = word[i];
  }
  result[length] = '\0';
  return result;
}
