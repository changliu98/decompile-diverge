

#include <assert.h>



int func0(int arr[], int n) {
  int minEle = arr[0];
  int maxEle = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] < minEle) {
      minEle = arr[i];
    }
    if (arr[i] > maxEle) {
      maxEle = arr[i];
    }
  }
  return (maxEle - minEle);
}
