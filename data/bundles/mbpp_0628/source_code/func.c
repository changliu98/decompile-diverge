

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <stdlib.h>



#define MAX 1000



char* func0(char* string) {
  char new_string[MAX];
  int i, j, space_count = 0, new_length;
  char* result;
  i = strlen(string);
  for (j = 0; j < i; j++) {
    if (string[j] == ' ') space_count++;
  }
  new_length = i + space_count * 2;
  if (new_length > MAX) {
    return "";
  }
  int index = new_length - 1;
  new_string[new_length] = '\0';
  for (j = i - 1; j >= 0; j--) {
    if (string[j] == ' ') {
      new_string[index] = '0';
      new_string[index - 1] = '2';
      new_string[index - 2] = '%';
      index -= 3;
    } else {
      new_string[index] = string[j];
      index--;
    }
  }
  result = (char*)malloc(new_length + 1);
  strcpy(result, new_string);
  return result;
}
