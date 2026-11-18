void cquat_sub(double *q,double *a,double *b)

{
  double *b_local;
  double *a_local;
  double *q_local;
  
  *q = *a - *b;
  q[1] = a[1] - b[1];
  q[2] = a[2] - b[2];
  q[3] = a[3] - b[3];
  return;
}