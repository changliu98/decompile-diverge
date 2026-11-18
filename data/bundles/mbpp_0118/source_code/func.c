

#include <assert.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>



char** func0(const char* string) {
  int count = 1;
  for (const char* ptr = string; *ptr; ptr++) {
    if (*ptr == ' ') {
      count++;
    }
  }
  char** list = malloc((count + 1) * sizeof(char*));
  if (!list) {
    return NULL;
  }
  char* str = strdup(string);
  if (!str) {
    free(list);
    return NULL;
  }
  int index = 0;
  char* token = strtok(str, " ");
  while (token != NULL) {
    list[index++] = strdup(token);
    token = strtok(NULL, " ");
  }
  list[index] = NULL;
  free(str);
  return list;
}
