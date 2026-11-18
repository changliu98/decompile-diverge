void __cdecl cspline2bezier(double *out, const double *in)
{
  int j; // [rsp+8h] [rbp-98h]
  int i; // [rsp+Ch] [rbp-94h]
  double m[4][4]; // [rsp+10h] [rbp-90h] BYREF
  const double *ina; // [rsp+90h] [rbp-10h]
  double *outa; // [rsp+98h] [rbp-8h]

  outa = out;
  ina = in;
  memset(m, 0, sizeof(m));
  m[0][0] = 1.0;
  m[0][1] = 1.0;
  m[1][1] = 0.3333333333333333;
  m[2][2] = 1.0;
  m[2][3] = 1.0;
  m[3][2] = -0.3333333333333333;
  for ( i = 0; i < 4; ++i )
  {
    outa[i] = 0.0;
    for ( j = 0; j < 4; ++j )
      outa[i] = m[j][i] * ina[j] + outa[i];
  }
}