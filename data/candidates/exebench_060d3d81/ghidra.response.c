void quatmul(double *r,double *p,double *q)

{
  double *q_local;
  double *p_local;
  double *r_local;
  
  *r = -p[3] * q[3] + -p[2] * q[2] + *p * *q + -(p[1] * q[1]);
  r[1] = -p[3] * q[2] + p[2] * q[3] + p[1] * *q + *p * q[1];
  r[2] = -p[1] * q[3] + p[3] * q[1] + p[2] * *q + *p * q[2];
  r[3] = -p[2] * q[1] + p[1] * q[2] + p[3] * *q + *p * q[3];
  return;
}