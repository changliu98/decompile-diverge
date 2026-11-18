void __cdecl mul_mat_vec_2(const float *m, const float *p, float *o)
{
  *o = (float)(*p * *m) + (float)(p[1] * m[1]);
  o[1] = (float)(*p * m[2]) + (float)(p[1] * m[3]);
}