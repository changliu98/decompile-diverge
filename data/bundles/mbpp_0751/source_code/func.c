

#include <stdbool.h>

#include <assert.h>



bool func0(int arr[], int n, int i) {
  if (2 * i + 2 > n) {
    return true;
  }
  bool left_child = (arr[i] <= arr[2 * i + 1]) && func0(arr, n, 2 * i + 1);
  bool right_child = (2 * i + 2 == n) || (arr[i] <= arr[2 * i + 2]
                                          && func0(arr, n, 2 * i + 2));
  return left_child && right_child;
}
