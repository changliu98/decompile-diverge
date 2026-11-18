int __cdecl zuchk_(double *yr, double *yi, int *nz, double *ascle, double *tol)
{
  double v6; // [rsp+0h] [rbp-70h]
  double v7; // [rsp+8h] [rbp-68h]
  double v8; // [rsp+10h] [rbp-60h]
  double v9; // [rsp+18h] [rbp-58h]

  *nz = 0;
  if ( *yr < 0.0 )
    *(_QWORD *)&v9 = *(_QWORD *)yr ^ 0x8000000000000000LL;
  else
    v9 = *yr;
  if ( *yi < 0.0 )
    *(_QWORD *)&v8 = *(_QWORD *)yi ^ 0x8000000000000000LL;
  else
    v8 = *yi;
  if ( v8 < v9 )
    v7 = v8;
  else
    v7 = v9;
  if ( v7 <= *ascle )
  {
    if ( v9 < v8 )
      v6 = v8;
    else
      v6 = v9;
    if ( v7 / *tol > v6 )
      *nz = 1;
  }
  return 0;
}