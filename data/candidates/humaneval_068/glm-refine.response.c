#include <limits.h>

int *find_smallest_even(int *arr, int length, int *output)
{
  int smallest_even = INT_MAX;
  int index = -1;

  // Find the smallest even number in the array
  for (int i = 0; i < length; ++i)
  {
    if (arr[i] % 2 == 0 && (index == -1 || arr[i] < smallest_even))
    {
      smallest_even = arr[i];
      index = i;
    }
  }

  // Return NULL if no even number was found
  if (index == -1)
    return NULL;

  // Store the result [smallest_even, index] in the output array
  output[0] = smallest_even;
  output[1] = index;
  
  return output;
}