int __cdecl func0(int *arr, int n)
{
  int sum = 0;
  
  for (int i = n - 1; i >= 0; --i)
  {
    // Algebraically simplified from: 
    // arr[i] * i - arr[i] * (n - 1 - i)
    sum += arr[i] * (2 * i - n + 1);
  }
  
  return sum;
}