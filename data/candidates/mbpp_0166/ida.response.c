int __cdecl func0(int *A, int N)
{
  int j; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]
  int evenPair; // [rsp+8h] [rbp-10h]

  evenPair = 0;
  for ( i = 0; i < N; ++i )
  {
    for ( j = i + 1; j < N; ++j )
    {
      if ( !((A[j] ^ A[i]) % 2) )
        ++evenPair;
    }
  }
  return evenPair;
}