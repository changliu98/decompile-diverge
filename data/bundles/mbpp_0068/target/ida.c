bool __cdecl func0(int *A, int n)
{
  bool v3; // [rsp+1h] [rbp-15h]
  int i; // [rsp+2h] [rbp-14h]
  char decreasing; // [rsp+8h] [rbp-Eh]
  bool increasing; // [rsp+9h] [rbp-Dh]

  increasing = 1;
  decreasing = 1;
  for ( i = 0; i < n - 1; ++i )
  {
    if ( A[i] > A[i + 1] )
      increasing = 0;
    if ( A[i] < A[i + 1] )
      decreasing = 0;
  }
  v3 = 1;
  if ( !increasing )
    return decreasing;
  return v3;
}