int __cdecl func0(int *A, int N)
{
  int evenPair = 0;
  
  for (int i = 0; i < N; ++i)
  {
    for (int j = i + 1; j < N; ++j)
    {
      // (A[i] ^ A[j]) & 1 checks the Least Significant Bit (LSB) of the XOR result.
      // If the LSB is 0, both numbers have the same parity.
      if (((A[i] ^ A[j]) & 1) == 0)
      {
        ++evenPair;
      }
    }
  }
  
  return evenPair;
}