

#include <assert.h>

#include <stdbool.h>



void re_arrange_array(int arr[], int n) {

    int j = 0;

    for (int i = 0; i < n; i++) {

        if (arr[i] < 0) {

            int temp = arr[i];

            arr[i] = arr[j];

            arr[j] = temp;

            j++;

        }

    }

}



bool func0(int arr1[], int arr2[], int n) {
  for (int i = 0; i < n; i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}
