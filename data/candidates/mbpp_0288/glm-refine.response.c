int __cdecl func0(int *arr, int N, int P)
{
  int count = 0;
  
  for (int i = 0; i < N; ++i)
  {
    // Check if arr[i] is a modular multiplicative inverse of itself modulo P
    if ( (arr[i] * arr[i]) % P == 1 )
    {
      ++count;
    }
  }
  
  return count;
}