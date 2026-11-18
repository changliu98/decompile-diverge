void lqtomat(double *q,double *rot)

{
  double *rot_local;
  double *q_local;
  
  *rot = -q[3] * q[3] + -q[2] * q[2] + *q * *q + q[1] * q[1];
  rot[1] = DAT_00102008 * (q[1] * q[2] + -(*q * q[3]));
  rot[2] = DAT_00102008 * (q[1] * q[3] + *q * q[2]);
  rot[3] = DAT_00102008 * (q[1] * q[2] + *q * q[3]);
  rot[4] = -q[3] * q[3] + q[2] * q[2] + *q * *q + -(q[1] * q[1]);
  rot[5] = DAT_00102008 * (q[2] * q[3] + -(*q * q[1]));
  rot[6] = DAT_00102008 * (q[1] * q[3] + -(*q * q[2]));
  rot[7] = DAT_00102008 * (q[2] * q[3] + *q * q[1]);
  rot[8] = q[3] * q[3] + -q[2] * q[2] + *q * *q + -(q[1] * q[1]);
  return;
}