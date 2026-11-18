void mul_mat_vec_2(float *m,float *p,float *o)

{
  float *o_local;
  float *p_local;
  float *m_local;
  
  *o = *p * *m + p[1] * m[1];
  o[1] = *p * m[2] + p[1] * m[3];
  return;
}