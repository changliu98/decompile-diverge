

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <ctype.h>



char* func0(const char* word, char* result) {
  int index = 0, capitalize = 1;
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == '_') {
      capitalize = 1;
    } else {
      if (capitalize) {
        result[index++] = toupper(word[i]);
        capitalize = 0;
      } else {
        result[index++] = word[i];
      }
    }
  }
  result[index] = '\0';
  return result;
}
