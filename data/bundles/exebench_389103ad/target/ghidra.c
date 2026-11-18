void atmtns(double *delta,double *v)

{
  double *v_local;
  double *delta_local;
  
  *v = *delta + *v;
  v[1] = delta[1] + v[1];
  v[2] = delta[2] + v[2];
  return;
}