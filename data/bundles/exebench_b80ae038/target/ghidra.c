void geom_matvec4d(double *m,double *u,double *v)

{
  double *v_local;
  double *u_local;
  double *m_local;
  
  *v = m[0xc] * u[3] + m[8] * u[2] + *m * *u + m[4] * u[1];
  v[1] = m[0xd] * u[3] + m[9] * u[2] + m[1] * *u + m[5] * u[1];
  v[2] = m[0xe] * u[3] + m[10] * u[2] + m[2] * *u + m[6] * u[1];
  v[3] = m[0xf] * u[3] + m[0xb] * u[2] + m[3] * *u + m[7] * u[1];
  return;
}