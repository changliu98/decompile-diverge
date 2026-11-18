

#include <stdio.h>

#include <assert.h>



int func0(int array[], int start, int end) {
  if (start > end) {
    return end + 1;
  }
  if (start != array[start]) {
    return start;
  }
  int mid = (start + end) / 2;
  if (array[mid] == mid) {
    return func0(array, mid + 1, end);
  }
  return func0(array, start, mid);
}
