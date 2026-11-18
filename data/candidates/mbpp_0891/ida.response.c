bool __cdecl func0(int A, int B)
{
  bool v3; // [rsp+1h] [rbp-Dh]

  while ( 1 )
  {
    v3 = 0;
    if ( A > 0 )
      v3 = B > 0;
    if ( !v3 )
      break;
    A /= 10;
    B /= 10;
  }
  return !A && !B;
}