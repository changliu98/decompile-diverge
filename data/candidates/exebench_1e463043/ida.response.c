int __cdecl c_insensitive(char *a, char *b)
{
  bool v3; // [rsp+1h] [rbp-1Dh]
  int x; // [rsp+2h] [rbp-1Ch]
  int xa; // [rsp+2h] [rbp-1Ch]
  int xb; // [rsp+2h] [rbp-1Ch]

  for ( x = 0; a[x]; ++x )
  {
    if ( a[x] > 96 && a[x] < 123 )
      a[x] -= 32;
  }
  for ( xa = 0; b[xa]; ++xa )
  {
    if ( b[xa] > 96 && b[xa] < 123 )
      b[xa] -= 32;
  }
  for ( xb = 0; ; ++xb )
  {
    v3 = 0;
    if ( a[xb] )
      v3 = b[xb] != 0;
    if ( !v3 )
      break;
    if ( a[xb] > b[xb] )
      return 1;
    if ( a[xb] < b[xb] )
      return -1;
  }
  return 0;
}