double __cdecl my_modf(double x0, double *iptr)
{
  double v2; // xmm0_8
  double i2; // [rsp+10h] [rbp-40h] BYREF
  double f; // [rsp+18h] [rbp-38h]
  double x; // [rsp+20h] [rbp-30h]
  long l; // [rsp+28h] [rbp-28h]
  int i; // [rsp+34h] [rbp-1Ch]
  double *iptra; // [rsp+38h] [rbp-18h]
  double x0a; // [rsp+40h] [rbp-10h]

  x0a = x0;
  iptra = iptr;
  x = x0;
  f = 1.0;
  for ( i = 0; i < 100; ++i )
  {
    l = (unsigned int)(int)x;
    if ( x + 1.0 >= (double)(int)x && (double)(int)l >= x - 1.0 )
      break;
    x = 0.1 * x;
    f = 10.0 * f;
  }
  if ( i == 100 )
  {
    *iptra = 0.0;
    return 0.0;
  }
  else if ( i )
  {
    v2 = my_modf(-(double)(int)l * f + x0a, &i2);
    *iptra = (double)(int)l * f + i2;
    return v2;
  }
  else
  {
    *iptra = (double)(int)l;
    return x - *iptra;
  }
}