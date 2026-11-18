void cspline2bezier(double *out,double *in)

{
  int j;
  int i;
  double m [4] [4];
  double *in_local;
  double *out_local;
  
  memset(m,0,0x80);
  m[0][0] = DAT_00102018;
  m[0][1] = DAT_00102018;
  m[1][1] = DAT_00102020;
  m[2][2] = DAT_00102018;
  m[2][3] = DAT_00102018;
  m[3][2] = DAT_00102010;
  for (i = 0; i < 4; i = i + 1) {
    out[i] = 0.0;
    for (j = 0; j < 4; j = j + 1) {
      out[i] = m[j][i] * in[j] + out[i];
    }
  }
  return;
}