#include <assert.h>

#include <stdio.h>



int func0(int arr[], int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    int count = 1;
    for (int j = 0; j < n; j++) {
      if (arr[j] == arr[i] && j != i) {
        count++;
      }
    }
    if (count > 1) {
      sum += arr[i];
    }
  }
  return sum;
}
