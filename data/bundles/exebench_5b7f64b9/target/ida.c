int __cdecl dspline(double *x, double *y, int n, int if1, double cond1, int ifn, double condn, double *y2)
{
  double sig; // [rsp+0h] [rbp-3EF8h]
  double un; // [rsp+8h] [rbp-3EF0h]
  double qn; // [rsp+10h] [rbp-3EE8h]
  double u[2000]; // [rsp+18h] [rbp-3EE0h]
  double p; // [rsp+3EA0h] [rbp-58h]
  int k; // [rsp+3EACh] [rbp-4Ch]
  int i__; // [rsp+3EB0h] [rbp-48h]
  int i__1; // [rsp+3EB4h] [rbp-44h]
  double *y2a; // [rsp+3EB8h] [rbp-40h]
  double condna; // [rsp+3EC0h] [rbp-38h]
  int ifna; // [rsp+3ECCh] [rbp-2Ch]
  double cond1a; // [rsp+3ED0h] [rbp-28h]
  int if1a; // [rsp+3ED8h] [rbp-20h]
  int na; // [rsp+3EDCh] [rbp-1Ch]
  double *ya; // [rsp+3EE0h] [rbp-18h]
  double *xa; // [rsp+3EE8h] [rbp-10h]

  na = n;
  if1a = if1;
  cond1a = cond1;
  ifna = ifn;
  condna = condn;
  y2a = y2 - 1;
  ya = y - 1;
  xa = x - 1;
  if ( n > 2000 )
    return 1;
  if ( if1a == 2 )
  {
    y2a[1] = 0.0;
    u[0] = cond1a;
  }
  else
  {
    if ( if1a != 1 )
      return 2;
    y2a[1] = -0.5;
    u[0] = 3.0 / (xa[2] - xa[1]) * ((ya[2] - ya[1]) / (xa[2] - xa[1]) - cond1a);
  }
  i__1 = na - 1;
  for ( i__ = 2; i__ <= i__1; ++i__ )
  {
    sig = (xa[i__] - xa[i__ - 1]) / (xa[i__ + 1] - xa[i__ - 1]);
    p = sig * y2a[i__ - 1] + 2.0;
    y2a[i__] = (sig - 1.0) / p;
    u[i__ - 1] = (COERCE_DOUBLE(*(_QWORD *)&sig ^ 0x8000000000000000LL) * u[i__ - 2]
                + ((ya[i__ + 1] - ya[i__]) / (xa[i__ + 1] - xa[i__]) - (ya[i__] - ya[i__ - 1]) / (xa[i__] - xa[i__ - 1]))
                * 6.0
                / (xa[i__ + 1] - xa[i__ - 1]))
               / p;
  }
  if ( ifna == 2 )
  {
    qn = 0.0;
    un = condna;
  }
  else
  {
    if ( ifna != 1 )
      return 3;
    qn = 0.5;
    un = 3.0 / (xa[na] - xa[na - 1]) * (condna - (ya[na] - ya[na - 1]) / (xa[na] - xa[na - 1]));
  }
  y2a[na] = (COERCE_DOUBLE(*(_QWORD *)&qn ^ 0x8000000000000000LL) * u[na - 2] + un) / (qn * y2a[na - 1] + 1.0);
  for ( k = na - 1; k >= 1; --k )
    y2a[k] = y2a[k] * y2a[k + 1] + u[k - 1];
  return 0;
}