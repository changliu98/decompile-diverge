int __cdecl func0(int x, int n)
{
  bool v3; // [rsp+1h] [rbp-15h]
  int count; // [rsp+2h] [rbp-14h]
  int p; // [rsp+6h] [rbp-10h]

  p = 1;
  for ( count = 0; ; ++count )
  {
    v3 = 0;
    if ( p <= x )
      v3 = count < 100;
    if ( !v3 )
      break;
    if ( p == x )
      return 1;
    p *= n;
  }
  return 0;
}