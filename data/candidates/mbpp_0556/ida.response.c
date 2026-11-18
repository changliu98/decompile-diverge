int __cdecl func0(int *A, int N)
{
  int j; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]
  int oddPair; // [rsp+8h] [rbp-10h]

  oddPair = 0;
  for ( i = 0; i < N; ++i )
  {
    for ( j = i + 1; j < N; ++j )
    {
      if ( (A[j] ^ A[i]) % 2 )
        ++oddPair;
    }
  }
  return oddPair;
}