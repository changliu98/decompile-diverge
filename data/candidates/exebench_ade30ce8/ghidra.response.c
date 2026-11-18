void cross_product(float *u,float *v,float *r)

{
  float *r_local;
  float *v_local;
  float *u_local;
  
  *r = u[1] * v[2] + -(u[2] * v[1]);
  r[1] = u[2] * *v + -(*u * v[2]);
  r[2] = *u * v[1] + -(u[1] * *v);
  return;
}