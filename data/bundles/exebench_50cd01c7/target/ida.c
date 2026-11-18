void __cdecl splini(double *xa, double *ya, double *y2a, int n, double x, double *y)
{
  bool v6; // [rsp+1h] [rbp-71h]
  double b; // [rsp+12h] [rbp-60h]
  double a; // [rsp+1Ah] [rbp-58h]
  double h; // [rsp+22h] [rbp-50h]
  double xx; // [rsp+2Ah] [rbp-48h]
  int khi; // [rsp+32h] [rbp-40h]
  int klo; // [rsp+36h] [rbp-3Ch]
  double yi; // [rsp+3Ah] [rbp-38h]

  yi = 0.0;
  klo = 0;
  for ( khi = 1; ; ++khi )
  {
    v6 = 0;
    if ( x > xa[klo] )
      v6 = khi < n;
    if ( !v6 )
      break;
    xx = x;
    if ( khi < n - 1 )
    {
      if ( xa[khi] <= x )
        xx = xa[khi];
      else
        xx = x;
    }
    h = xa[khi] - xa[klo];
    a = (xa[khi] - xx) / h;
    b = (xx - xa[klo]) / h;
    yi = ((1.0 - a * a) * ya[klo] / 2.0
        + b * b * ya[khi] / 2.0
        + ((-(a * a * (a * a) + 1.0) / 4.0 + a * a / 2.0) * y2a[klo] + (b * b * (b * b) / 4.0 - b * b / 2.0) * y2a[khi])
        * h
        * h
        / 6.0)
       * h
       + yi;
    ++klo;
  }
  *y = yi;
}