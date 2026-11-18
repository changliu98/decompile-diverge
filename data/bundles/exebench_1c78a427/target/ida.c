void __cdecl cquat_to_matrix_t(const double *q, double *m)
{
  double v2; // xmm1_8
  double v3; // xmm1_8
  double v4; // xmm1_8

  v2 = q[2] * q[2] + q[1] * q[1];
  *m = 1.0 - (v2 + v2);
  m[1] = 2.0 * (q[2] * q[3] + q[1] * *q);
  m[2] = 2.0 * (q[2] * *q - q[1] * q[3]);
  m[3] = 2.0 * (*q * q[1] - q[2] * q[3]);
  v3 = *q * *q + q[2] * q[2];
  m[4] = 1.0 - (v3 + v3);
  m[5] = 2.0 * (*q * q[3] + q[2] * q[1]);
  m[6] = 2.0 * (q[1] * q[3] + *q * q[2]);
  m[7] = 2.0 * (q[1] * q[2] - *q * q[3]);
  v4 = q[1] * q[1] + *q * *q;
  m[8] = 1.0 - (v4 + v4);
}