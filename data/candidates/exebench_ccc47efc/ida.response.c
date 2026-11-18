double __cdecl determinant_3x3(float *inp)
{
  double m[3][3]; // [rsp+0h] [rbp-60h] BYREF
  double det; // [rsp+48h] [rbp-18h]
  int j; // [rsp+50h] [rbp-10h]
  int i; // [rsp+54h] [rbp-Ch]
  float *inpa; // [rsp+58h] [rbp-8h]

  inpa = inp;
  det = 0.0;
  memset(m, 0, sizeof(m));
  for ( i = 0; i < 3; ++i )
  {
    for ( j = 0; j < 3; ++j )
      m[i][j] = inpa[3 * j + i];
  }
  return m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0])
       + COERCE_DOUBLE(*(_QWORD *)&m[0][1] ^ 0x8000000000000000LL) * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
       + m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
}