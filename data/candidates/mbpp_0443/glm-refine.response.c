// This function finds the minimum value in an array of integers.
// Note: The variable originally named "max" actually tracks the minimum value.
// Note: If size is 0, this function will result in undefined behavior due to 
// dereferencing the first element before the loop.
int __cdecl find_min(int *arr, int size)
{
  int i;
  int min_val;

  min_val = arr[0];
  for (i = 0; i < size; ++i)
  {
    if (arr[i] < min_val)
      min_val = arr[i];
  }
  return min_val;
}