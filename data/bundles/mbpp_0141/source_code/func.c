

#include <assert.h>

#include <stdio.h>



void reverse(int arr[], int start, int end) {

    while (start < end) {

        int temp = arr[start];

        arr[start] = arr[end];

        arr[end] = temp;

        start++;

        end--;

    }

}



int find_max_index(int arr[], int n) {

    int max_idx = 0;

    for (int i = 1; i < n; i++) {

        if (arr[i] > arr[max_idx]) {

            max_idx = i;

        }

    }

    return max_idx;

}



void func0(int arr[], int n) {
  for (int curr_size = n; curr_size > 1; --curr_size) {
    int max_idx = find_max_index(arr, curr_size);
    if (max_idx != curr_size - 1) {
      reverse(arr, 0, max_idx);
      reverse(arr, 0, curr_size - 1);
    }
  }
}
