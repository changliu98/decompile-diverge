void cquat_set(double *q,double x,double y,double z,double w)

{
  double w_local;
  double z_local;
  double y_local;
  double x_local;
  double *q_local;
  
  *q = x;
  q[1] = y;
  q[2] = z;
  q[3] = w;
  return;
}