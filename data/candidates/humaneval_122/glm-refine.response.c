#include <stdlib.h> // For abs()

int sum_small_values(int *arr, int count)
{
  int sum = 0;
  
  for (int i = 0; i < count; ++i)
  {
    // Check if the absolute value is less than or equal to 99
    if (abs(arr[i]) <= 99)
    {
      sum += arr[i];
    }
  }
  
  return sum;
}