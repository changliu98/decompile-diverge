

#include <stdio.h>

#include <assert.h>



int func0(int arr[], int n) {
  int mpis[n];
  for (int i = 0; i < n; i++) {
    mpis[i] = arr[i];
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j] && mpis[i] < (mpis[j] * arr[i])) {
        mpis[i] = mpis[j] * arr[i];
      }
    }
  }
  int maxVal = mpis[0];
  for (int i = 1; i < n; i++) {
    if (mpis[i] > maxVal) {
      maxVal = mpis[i];
    }
  }
  return maxVal;
}
