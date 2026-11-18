

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>



int func0(const char *input) {
  int max = 0;
  char temp[256];
  int index = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] >= '0' && input[i] <= '9') {
      temp[index++] = input[i];
    } else {
      if (index != 0) {
        temp[index] = '\0';
        int number = atoi(temp);
        if (number > max) max = number;
        index = 0;
      }
    }
  }
  if (index != 0) {
    temp[index] = '\0';
    int number = atoi(temp);
    if (number > max) max = number;
  }
  return max;
}
