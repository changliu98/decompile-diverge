void vec3d_set(double *v,double a,double b,double c)

{
  double c_local;
  double b_local;
  double a_local;
  double *v_local;
  
  *v = a;
  v[1] = b;
  v[2] = c;
  return;
}