int __cdecl func0(int *A, int n)
{
  int temp; // [rsp+0h] [rbp-20h]
  int j; // [rsp+4h] [rbp-1Ch]
  int i; // [rsp+8h] [rbp-18h]
  int ia; // [rsp+8h] [rbp-18h]

  for ( i = 0; i < n; ++i )
  {
    for ( j = i + 1; j < n; ++j )
    {
      if ( A[i] > A[j] )
      {
        temp = A[j];
        A[j] = A[i];
        A[i] = temp;
      }
    }
  }
  for ( ia = n - 1; ia >= 0; --ia )
  {
    if ( is_palindrome(A[ia]) )
      return A[ia];
  }
  return -1;
}