#include <assert.h>



int func0(int li[], int size, int min, int max) {
  int ctr = 0;
  for (int i = 0; i < size; i++) {
    if (li[i] >= min && li[i] <= max) {
      ctr++;
    }
  }
  return ctr;
}
