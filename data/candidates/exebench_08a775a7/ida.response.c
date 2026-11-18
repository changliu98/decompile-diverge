int __cdecl next(int *mask, int n)
{
  bool v3; // [rsp+1h] [rbp-19h]
  int i; // [rsp+2h] [rbp-18h]

  for ( i = 0; ; ++i )
  {
    v3 = 0;
    if ( i < n )
      v3 = mask[i] != 0;
    if ( !v3 )
      break;
    mask[i] = 0;
  }
  if ( i >= n )
    return 0;
  mask[i] = 1;
  return 1;
}