

#include <assert.h>

#include <limits.h>



int func0(int listval[], int size) {
  int max_val = INT_MIN;
  for (int i = 0; i < size; i++) {
    if (listval[i] > max_val) {
      max_val = listval[i];
    }
  }
  return max_val;
}
