void mult_xps_vec(float *v,float *M,float *u)

{
  float *u_local;
  float *M_local;
  float *v_local;
  
  *v = M[3] * u[3] + M[2] * u[2] + *M * *u + M[1] * u[1];
  v[1] = M[7] * u[3] + M[6] * u[2] + M[4] * *u + M[5] * u[1];
  v[2] = M[0xb] * u[3] + M[10] * u[2] + M[8] * *u + M[9] * u[1];
  v[3] = M[0xf] * u[3] + M[0xe] * u[2] + M[0xc] * *u + M[0xd] * u[1];
  return;
}