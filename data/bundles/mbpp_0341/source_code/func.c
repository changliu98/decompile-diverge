#include <stdio.h>

#include <assert.h>

#include <stdlib.h>



int cmpfunc (const void * a, const void * b) {

   return ( *(int*)a - *(int*)b );

}



void func0(int arr[], int n, int result[]) {
  qsort(arr, n, sizeof(int), cmpfunc);
  for (int i = 0; i < n; i++) {
    result[i] = arr[i];
  }
}
