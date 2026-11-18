void __cdecl lqtomat(double *q, double *rot)
{
  *rot = COERCE_DOUBLE(*((_QWORD *)q + 3) ^ 0x8000000000000000LL) * q[3]
       + COERCE_DOUBLE(*((_QWORD *)q + 2) ^ 0x8000000000000000LL) * q[2]
       + *q * *q
       + q[1] * q[1];
  rot[1] = 2.0 * (q[1] * q[2] - *q * q[3]);
  rot[2] = 2.0 * (q[1] * q[3] + *q * q[2]);
  rot[3] = 2.0 * (q[1] * q[2] + *q * q[3]);
  rot[4] = COERCE_DOUBLE(*((_QWORD *)q + 3) ^ 0x8000000000000000LL) * q[3] + q[2] * q[2] + *q * *q - q[1] * q[1];
  rot[5] = 2.0 * (q[2] * q[3] - *q * q[1]);
  rot[6] = 2.0 * (q[1] * q[3] - *q * q[2]);
  rot[7] = 2.0 * (q[2] * q[3] + *q * q[1]);
  rot[8] = q[3] * q[3] + COERCE_DOUBLE(*((_QWORD *)q + 2) ^ 0x8000000000000000LL) * q[2] + *q * *q - q[1] * q[1];
}