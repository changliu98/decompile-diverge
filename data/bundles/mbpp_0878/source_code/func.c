

#include <stdbool.h>

#include <assert.h>



bool func0(int test_tuple[], int tuple_size, int K[], int K_size) {
  for (int i = 0; i < tuple_size; i++) {
    bool found = false;
    for (int j = 0; j < K_size; j++) {
      if (test_tuple[i] == K[j]) {
        found = true;
        break;
      }
    }
    if (!found) {
      return false;
    }
  }
  return true;
}
