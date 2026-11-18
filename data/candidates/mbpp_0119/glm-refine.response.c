int __cdecl func0(int *arr, int n)
{
  int xor_sum = 0;
  for (int i = 0; i < n; ++i)
    xor_sum ^= arr[i];
  return xor_sum;
}