void subtract(float *u,float *v,float *r)

{
  float *r_local;
  float *v_local;
  float *u_local;
  
  *r = *u - *v;
  r[1] = u[1] - v[1];
  r[2] = u[2] - v[2];
  return;
}