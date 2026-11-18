int __cdecl func0(int *A, int N)
{
  int oddPair = 0;
  
  for (int i = 0; i < N; ++i)
  {
    for (int j = i + 1; j < N; ++j)
    {
      // (A[j] ^ A[i]) % 2 is equivalent to (A[j] % 2) ^ (A[i] % 2)
      // This effectively checks if the two numbers have different parities (one is odd, the other is even)
      if ((A[i] & 1) != (A[j] & 1))
        ++oddPair;
    }
  }
  
  return oddPair;
}