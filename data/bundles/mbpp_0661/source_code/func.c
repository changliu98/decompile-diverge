

#include <stdio.h>

#include <assert.h>



int func0(int arr[], int n) {
  int sum[n];
  if (n >= 1) sum[0] = arr[0];
  if (n >= 2) sum[1] = arr[0] + arr[1];
  if (n > 2)
    sum[2] = (sum[1] > (arr[1] + arr[2]) ? sum[1] : (arr[1] + arr[2])) >
                     (arr[0] + arr[2])
                 ? (sum[1] > (arr[1] + arr[2]) ? sum[1] : (arr[1] + arr[2]))
                 : (arr[0] + arr[2]);
  for (int i = 3; i < n; i++) {
    int max1 = sum[i - 1];
    int max2 = sum[i - 2] + arr[i];
    int max3 = arr[i] + arr[i - 1] + sum[i - 3];
    sum[i] =
        (max1 > max2 ? max1 : max2) > max3 ? (max1 > max2 ? max1 : max2) : max3;
  }
  return sum[n - 1];
}
