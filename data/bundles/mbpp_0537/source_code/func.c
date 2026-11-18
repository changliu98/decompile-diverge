

#include <stdio.h>

#include <string.h>

#include <assert.h>



char *func0(char *str1) {
  char *words[100];
  int word_count = 0;
  char *word = strtok(str1, " ");
  while (word != NULL) {
    for (int i = 0; i < word_count; i++) {
      if (strcmp(words[i], word) == 0) {
        return word;
      }
    }
    words[word_count++] = word;
    word = strtok(NULL, " ");
  }
  return "None";
}
