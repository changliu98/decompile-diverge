int matMultMVf(float *m,float *v,float *r)

{
  float *r_local;
  float *v_local;
  float *m_local;
  
  *r = m[3] * v[3] + m[2] * v[2] + *m * *v + m[1] * v[1];
  r[1] = m[7] * v[3] + m[6] * v[2] + m[4] * *v + m[5] * v[1];
  r[2] = m[0xb] * v[3] + m[10] * v[2] + m[8] * *v + m[9] * v[1];
  r[3] = m[0xf] * v[3] + m[0xe] * v[2] + m[0xc] * *v + m[0xd] * v[1];
  return 0;
}