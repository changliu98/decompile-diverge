#include <stdlib.h>

void __cdecl merge_sort(int *arr, int len)
{
  int i;
  int mid;
  int *left;
  int *right;

  if (len >= 2)
  {
    mid = len / 2;
    
    // Allocate memory for the two halves
    left = (int *)malloc(sizeof(int) * mid);
    right = (int *)malloc(sizeof(int) * (len - mid));

    // Copy data to the left subarray
    for (i = 0; i < mid; ++i)
      left[i] = arr[i];

    // Copy data to the right subarray
    for (i = 0; i < len - mid; ++i)
      right[i] = arr[mid + i];

    // Recursively sort both halves
    merge_sort(left, mid);
    merge_sort(right, len - mid);

    // Merge the sorted halves back into the original array
    merge(left, mid, right, len - mid, arr);

    // Free the allocated memory
    free(left);
    free(right);
  }
}