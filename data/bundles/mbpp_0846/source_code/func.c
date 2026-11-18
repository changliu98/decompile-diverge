

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>



int compare(const void *a, const void *b) {

    return (*(int*)a - *(int*)b);

}



int func0(int arr[], int dep[], int n) {
  qsort(arr, n, sizeof(int), compare);
  qsort(dep, n, sizeof(int), compare);
  int plat_needed = 1, result = 1;
  int i = 1, j = 0;
  while (i < n && j < n) {
    if (arr[i] <= dep[j]) {
      plat_needed++;
      i++;
      if (plat_needed > result) {
        result = plat_needed;
      }
    } else {
      plat_needed--;
      j++;
    }
  }
  return result;
}
