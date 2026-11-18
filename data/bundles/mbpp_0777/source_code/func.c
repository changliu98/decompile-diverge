

#include <stdio.h>

#include <assert.h>

#include <stdlib.h>



int compare(const void* a, const void* b) {

    return (*(int*)a - *(int*)b);

}



int func0(int* arr, int n) {
  qsort(arr, n, sizeof(int), compare);
  int sum = arr[0];
  for (int i = 0; i < n - 1; i++) {
    if (arr[i] != arr[i + 1]) {
      sum += arr[i + 1];
    }
  }
  return sum;
}
