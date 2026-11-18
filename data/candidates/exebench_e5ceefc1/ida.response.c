int __cdecl set1d(double *arr, double value)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 40; ++i )
    arr[i] = value;
  return 0;
}