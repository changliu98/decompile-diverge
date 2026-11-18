int __cdecl func0(int A, int N, int L, int R)
{
  int count; // [rsp+4h] [rbp-14h]

  count = 0;
  while ( L <= R )
  {
    if ( L % A )
      ++count;
    if ( count == N )
      break;
    ++L;
  }
  return L;
}