void cquat_to_matrix_t(double *q,double *m)

{
  double dVar1;
  double *m_local;
  double *q_local;
  
  dVar1 = q[2] * q[2] + q[1] * q[1];
  *m = DAT_00102008 - (dVar1 + dVar1);
  m[1] = DAT_00102010 * (q[2] * q[3] + q[1] * *q);
  m[2] = DAT_00102010 * (q[2] * *q + -(q[1] * q[3]));
  m[3] = DAT_00102010 * (*q * q[1] + -(q[2] * q[3]));
  dVar1 = *q * *q + q[2] * q[2];
  m[4] = DAT_00102008 - (dVar1 + dVar1);
  m[5] = DAT_00102010 * (*q * q[3] + q[2] * q[1]);
  m[6] = DAT_00102010 * (q[1] * q[3] + *q * q[2]);
  m[7] = DAT_00102010 * (q[1] * q[2] + -(*q * q[3]));
  dVar1 = q[1] * q[1] + *q * *q;
  m[8] = DAT_00102008 - (dVar1 + dVar1);
  return;
}