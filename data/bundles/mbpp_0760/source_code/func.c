

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>



const char* func0(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    if (arr[i] != arr[0]) {
      return "NO";
    }
  }
  return "YES";
}
