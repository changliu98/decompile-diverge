

#include <stdio.h>

#include <assert.h>



void shift_down(int arr[], int start, int end) {

    int root = start;

    while (root * 2 + 1 <= end) {

        int child = root * 2 + 1;

        if (child + 1 <= end && arr[child] < arr[child + 1]) {

            child += 1;

        }

        if (child <= end && arr[root] < arr[child]) {

            int temp = arr[root];

            arr[root] = arr[child];

            arr[child] = temp;

            root = child;

        } else {

            return;

        }

    }

}



void heapify(int arr[], int length) {

    int start = (length - 2) / 2;

    while (start >= 0) {

        shift_down(arr, start, length - 1);

        start -= 1;

    }

}



void func0(int arr[], int length) {
  heapify(arr, length);
  int end = length - 1;
  while (end > 0) {
    int temp = arr[end];
    arr[end] = arr[0];
    arr[0] = temp;
    end -= 1;
    shift_down(arr, 0, end);
  }
}
