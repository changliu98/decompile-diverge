void quad_2_grad(double *grad,double *g,double *H,double *r)

{
  double *r_local;
  double *H_local;
  double *g_local;
  double *grad_local;
  
  *grad = *g + *H * *r + H[1] * r[1];
  grad[1] = g[1] + H[1] * *r + H[2] * r[1];
  return;
}