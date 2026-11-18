void vmul(float *v, float *s, float *r)
{
  r[0] = r[0] + v[0] * s[0];
  r[1] = r[1] + v[1] * s[0];
}