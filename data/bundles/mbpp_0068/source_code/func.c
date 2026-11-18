

#include <stdbool.h>

#include <assert.h>



bool func0(int A[], int n) {
  bool increasing = true;
  bool decreasing = true;
  for (int i = 0; i < n - 1; i++) {
    if (A[i] > A[i + 1]) {
      increasing = false;
    }
    if (A[i] < A[i + 1]) {
      decreasing = false;
    }
  }
  return increasing || decreasing;
}
