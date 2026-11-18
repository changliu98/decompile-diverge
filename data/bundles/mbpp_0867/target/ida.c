int __cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-1Ch]
  int odd; // [rsp+4h] [rbp-18h]

  odd = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( arr[i] % 2 )
      ++odd;
  }
  if ( odd % 2 )
    return 1;
  else
    return 2;
}