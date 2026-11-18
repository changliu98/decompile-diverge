void s_det2(float *v)
{
  float a; float b; float c; float d;
  a = v[0] + v[6];
  b = v[0] - v[6];
  c = v[1] + v[2];
  d = v[1] - v[2];
  v[6] = a + c;
  v[4] = a - c;
  a = v[3] - v[5];
  c = v[7] - v[4];
  v[0] = b + a;
  v[2] = b - a;
  a = v[3] + v[5];
  c = v[7] + v[4];
  v[4] = c - d;
  v[1] = c + d;
  v[7] = a + c;
  v[5] = a - c;
}