// Finds and returns the minimum value in an array of integers.
// Note: If the array size is 0, it returns 0x7FFFFFFF (INT_MAX).
int __cdecl array_min(int *array, int size)
{
  int min_val = 0x7FFFFFFF; // INT_MAX
  
  for (int i = 0; i < size; ++i)
  {
    if (array[i] < min_val)
    {
      min_val = array[i];
    }
  }
  
  return min_val;
}