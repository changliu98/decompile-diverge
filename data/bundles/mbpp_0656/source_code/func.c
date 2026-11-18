

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>



void sort(int arr[], int n) {

    int i, j;

    for (i = 0; i < n - 1; i++) {

        for (j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];

                arr[j] = arr[j + 1];

                arr[j + 1] = temp;

            }

        }

    }

}



int func0(int a[], int b[], int n) {
  sort(a, n);
  sort(b, n);
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += abs(a[i] - b[i]);
  }
  return sum;
}
