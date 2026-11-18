

#include <stdbool.h>

#include <assert.h>

#include <stdlib.h>



bool func0(int *l, int size) {
  int *sorted = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    sorted[i] = l[i];
  }
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (sorted[i] > sorted[j]) {
        int temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = temp;
      }
    }
  }
  bool result = true;
  for (int i = 1; i < size; i++) {
    if (sorted[i] != sorted[i - 1] + 1) {
      result = false;
      break;
    }
  }
  free(sorted);
  return result;
}
