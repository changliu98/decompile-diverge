

#include <assert.h>

#include <limits.h>

#include <stdio.h>



int func0(char *listval[], int size) {
  int min_val = INT_MAX;
  int current_val;
  for (int i = 0; i < size; i++) {
    if (sscanf(listval[i], "%d", &current_val)) {
      if (current_val < min_val) {
        min_val = current_val;
      }
    }
  }
  return min_val;
}
