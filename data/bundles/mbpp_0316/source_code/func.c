

#include <assert.h>



int func0(int A[], int n, int x) {
  int left = 0;
  int right = n - 1;
  int result = -1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (x == A[mid]) {
      result = mid;
      left = mid + 1;
    } else if (x < A[mid]) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return result;
}
