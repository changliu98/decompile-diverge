#include <assert.h>



int func0(int lst[], int size) {
  int total = 0;
  for (int i = 0; i < size; i++) {
    total += lst[i];
  }
  return total;
}
