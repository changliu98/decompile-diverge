void scal3(double scal,double *v)

{
  double *v_local;
  double scal_local;
  
  *v = scal * *v;
  v[1] = scal * v[1];
  v[2] = scal * v[2];
  return;
}