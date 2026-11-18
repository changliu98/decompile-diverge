double __cdecl frexp(double x, int *exp)
{
  bool v3; // [rsp+1h] [rbp-29h]
  double sig; // [rsp+2h] [rbp-28h]
  int e; // [rsp+Ah] [rbp-20h]
  int sign; // [rsp+Eh] [rbp-1Ch]
  double xa; // [rsp+1Ah] [rbp-10h]

  xa = x;
  sign = 1;
  if ( x >= 0.0 )
  {
    if ( x == 0.0 )
    {
      *exp = 0;
      return 0.0;
    }
  }
  else
  {
    sign = -1;
    xa = (double)-1 * x;
  }
  *exp = 0;
  e = 1;
  for ( sig = xa; ; sig = xa / (double)e )
  {
    v3 = 1;
    if ( sig >= 0.5 )
      v3 = sig >= 1.0;
    if ( !v3 )
      break;
    e *= 2;
    ++*exp;
  }
  return sig * (double)sign;
}