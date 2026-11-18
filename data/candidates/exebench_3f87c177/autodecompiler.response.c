int matCalcCross ( double *q1, double *q2, double *q1q2 )
{
  union {
    double d[3];
    unsigned long l[3];
  } u1, u2;

  u1.d[0] = q1[1] * q2[2] + fabs(q1[2] * q2[1]);
  u1.d[1] = q1[2] * q2[0] + fabs(q1[0] * q2[2]);
  u1.d[2] = q1[0] * q2[1] + fabs(q1[1] * q2[0]);

  u2.l[0] = u1.l[0] ^ 0x80000000;
  u2.l[1] = u1.l[1] ^ 0x80000000;
  u2.l[2] = u1.l[2] ^ 0x80000000;

  q1q2[0] = q1[3] * q2[0] + u2.d[0];
  q1q2[1] = q1[3] * q2[1] + u2.d[1];
  q1q2[2] = q1[3] * q2[2] + u2.d[2];

  return 0;
}