int __cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-14h]
  int XOR; // [rsp+4h] [rbp-10h]

  XOR = 0;
  for ( i = 0; i < n; ++i )
    XOR ^= arr[i];
  return XOR;
}