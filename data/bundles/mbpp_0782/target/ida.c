int __cdecl func0(int *arr, int l)
{
  int i; // [rsp+0h] [rbp-14h]
  int Sum; // [rsp+4h] [rbp-10h]

  Sum = 0;
  for ( i = 0; i < l; ++i )
    Sum += arr[i] * (((l - i) * (i + 1) + 1) / 2);
  return Sum;
}