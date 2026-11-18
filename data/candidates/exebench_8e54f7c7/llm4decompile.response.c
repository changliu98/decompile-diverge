void cspline2bezier(bezier_t *out, const cspline_t *in)
{
 double m[4][4];
 memset(m, 0, sizeof(m));
 m[0][0] = 1.0;
 m[0][1] = 1.0;
 m[1][1] = -2.0;
 m[2][2] = 1.0;
 m[2][3] = 1.0;
 m[3][2] = -1.0;

 int i, j;
 for (i = 0; i < 4; i++) {
  out[i] = 0.0;
  for (j = 0; j < 4; j++) {
   out[i] += m[j][i] * in[j];
  }
 }
}