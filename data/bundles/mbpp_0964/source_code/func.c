#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>



int func0(char* s) {
  char* word = strtok(s, " ");
  while (word != NULL) {
    if (strlen(word) % 2 == 0) {
      return 1;
    } else {
      return 0;
    }
    word = strtok(NULL, " ");
  }
  return 0;
}
