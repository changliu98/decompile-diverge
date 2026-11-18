double __cdecl frexp(double x, int *exp)
{
  double s; // [rsp+0h] [rbp-20h]
  int n; // [rsp+Ch] [rbp-14h]
  double xa; // [rsp+18h] [rbp-8h]

  xa = x;
  n = 0;
  s = 1.0;
  if ( x < 0.0 )
  {
    *(_QWORD *)&xa = *(_QWORD *)&x ^ 0x8000000000000000LL;
    s = -1.0;
  }
  if ( xa != 0.0 )
  {
    for ( ; xa >= 1.0; xa = 0.5 * xa )
      ++n;
    for ( ; xa < 0.5; xa = 2.0 * xa )
      --n;
  }
  *exp = n;
  return xa * s;
}