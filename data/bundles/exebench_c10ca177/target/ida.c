void __cdecl geom_matinv2d(double *m)
{
  double t; // [rsp+0h] [rbp-18h]
  double d; // [rsp+8h] [rbp-10h]

  d = 1.0 / (*m * m[3] - m[1] * m[2]);
  t = *m;
  *m = d * m[3];
  m[1] = COERCE_DOUBLE(*(_QWORD *)&d ^ 0x8000000000000000LL) * m[1];
  m[2] = COERCE_DOUBLE(*(_QWORD *)&d ^ 0x8000000000000000LL) * m[2];
  m[3] = d * t;
}