void geom_matvec3f(float *m,float *u,float *v)

{
  float *v_local;
  float *u_local;
  float *m_local;
  
  *v = m[6] * u[2] + *m * *u + m[3] * u[1];
  v[1] = m[7] * u[2] + m[1] * *u + m[4] * u[1];
  v[2] = m[8] * u[2] + m[2] * *u + m[5] * u[1];
  return;
}