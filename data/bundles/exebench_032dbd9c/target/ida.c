void __cdecl poly_mul1(double *u1, double *u2, int p1, int p2, double *u3, int *p3)
{
  double u1i; // [rsp+0h] [rbp-40h]
  int i2; // [rsp+Ch] [rbp-34h]
  int i1; // [rsp+10h] [rbp-30h]
  int i; // [rsp+14h] [rbp-2Ch]

  *p3 = p2 + p1;
  for ( i = 0; i < 17; ++i )
    u3[i] = 0.0;
  for ( i1 = 0; i1 <= p1; ++i1 )
  {
    u1i = u1[i1];
    for ( i2 = 0; i2 <= p2; ++i2 )
      u3[i2 + i1] = u1i * u2[i2] + u3[i2 + i1];
  }
}