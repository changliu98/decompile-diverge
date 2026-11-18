int __cdecl func0(int *arr, int n)
{
  int sum = 0;

  // Iterate through the array, jumping by 2 (evaluating every even-indexed element)
  for (int i = 0; i < n; i += 2)
  {
    // Check if the element at the even index is itself an even number
    if (arr[i] % 2 == 0)
    {
      sum += arr[i];
    }
  }
  
  return sum;
}