

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>



void merge(int a[], int a_len, int b[], int b_len, int c[]) {

    int i = 0, j = 0, k = 0;

    while (i < a_len && j < b_len) {

        if (a[i] < b[j]) {

            c[k++] = a[i++];

        } else {

            c[k++] = b[j++];

        }

    }

    while (i < a_len) {

        c[k++] = a[i++];

    }

    while (j < b_len) {

        c[k++] = b[j++];

    }

}



void func0(int arr[], int len) {
  if (len < 2) {
    return;
  }
  int mid = len / 2;
  int *left = (int *)malloc(mid * sizeof(int));
  int *right = (int *)malloc((len - mid) * sizeof(int));
  for (int i = 0; i < mid; i++) {
    left[i] = arr[i];
  }
  for (int i = mid; i < len; i++) {
    right[i - mid] = arr[i];
  }
  func0(left, mid);
  func0(right, len - mid);
  merge(left, mid, right, len - mid, arr);
  free(left);
  free(right);
}
