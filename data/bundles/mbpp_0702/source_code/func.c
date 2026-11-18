#include <stdlib.h>

#include <stdio.h>

#include <assert.h>

#include <string.h>

int find_ind(int key, int i, int n, int k, int arr[]) {

    int ind = -1;

    int start = i + 1;

    int end = n - 1;

    while (start < end) {

        int mid = start + (end - start) / 2;

        if (arr[mid] - key <= k) {

            ind = mid;

            start = mid + 1;

        } else {

            end = mid;

        }

    }

    return ind;

}



int func0(int arr[], int n, int k) {
  int ans = n - 1;
  qsort(arr, n, sizeof(int), (int (*)(const void *, const void *))strcmp);
  for (int i = 0; i < n; i++) {
    int j = find_ind(arr[i], i, n, k, arr);
    if (j != -1) {
      ans = (ans < n - (j - i + 1) ? ans : n - (j - i + 1));
    }
  }
  return ans;
}
