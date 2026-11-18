

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>



void sortArray(int *arr, int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - 1 - i; j++) {

            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];

                arr[j] = arr[j + 1];

                arr[j + 1] = temp;

            }

        }

    }

}



int func0(int *arr, int n) {
  sortArray(arr, n);
  int count = 0, max_count = 0, min_count = n;
  for (int i = 0; i < n - 1; i++) {
    if (arr[i] == arr[i + 1]) {
      count++;
      continue;
    } else {
      max_count = (max_count > count) ? max_count : count;
      min_count = (min_count < count) ? min_count : count;
      count = 0;
    }
  }
  return max_count - min_count;
}
