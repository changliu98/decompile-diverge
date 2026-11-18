void mult_mat_vec(float *v,float *M,float *u)

{
  float *u_local;
  float *M_local;
  float *v_local;
  
  *v = M[0xc] * u[3] + M[8] * u[2] + *M * *u + M[4] * u[1];
  v[1] = M[0xd] * u[3] + M[9] * u[2] + M[1] * *u + M[5] * u[1];
  v[2] = M[0xe] * u[3] + M[10] * u[2] + M[2] * *u + M[6] * u[1];
  v[3] = M[0xf] * u[3] + M[0xb] * u[2] + M[3] * *u + M[7] * u[1];
  return;
}