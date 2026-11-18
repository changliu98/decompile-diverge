

#include <assert.h>



int func0(int list1[], int size) {
  int max = list1[0];
  for (int i = 0; i < size; i++) {
    if (list1[i] < max) {
      max = list1[i];
    }
  }
  return max;
}
