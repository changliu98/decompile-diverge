void __cdecl rgb2cmyk(double r, double g, double b, double *c, double *m, double *y, double *k)
{
  __int64 v7; // [rsp+0h] [rbp-48h]
  __int64 v8; // [rsp+8h] [rbp-40h]

  *c = 1.0 - r;
  *m = 1.0 - g;
  *y = 1.0 - b;
  if ( *m <= *c )
    v8 = *(_QWORD *)m;
  else
    v8 = *(_QWORD *)c;
  *(_QWORD *)k = v8;
  if ( *k <= *y )
    v7 = *(_QWORD *)k;
  else
    v7 = *(_QWORD *)y;
  *(_QWORD *)k = v7;
  *c = *c - *k;
  *m = *m - *k;
  *y = *y - *k;
}