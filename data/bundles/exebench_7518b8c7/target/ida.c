int __cdecl max(float *arr)
{
  float highest; // [rsp+0h] [rbp-14h]
  int ret; // [rsp+4h] [rbp-10h]
  int i; // [rsp+8h] [rbp-Ch]

  ret = 0;
  highest = *arr;
  for ( i = 0; (unsigned __int64)i < 2; ++i )
  {
    if ( arr[i] > highest )
    {
      ret = i;
      highest = arr[i];
    }
  }
  return ret;
}