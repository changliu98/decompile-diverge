void __cdecl subtract(float *u, float *v, float *r)
{
  *r = *u - *v;
  r[1] = u[1] - v[1];
  r[2] = u[2] - v[2];
}