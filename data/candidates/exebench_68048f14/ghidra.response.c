void vinv(double *v)

{
  double *v_local;
  
  *v = -*v;
  v[1] = -v[1];
  v[2] = -v[2];
  return;
}