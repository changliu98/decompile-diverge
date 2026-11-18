void __cdecl quatmul(double *r, double *p, double *q)
{
  *r = COERCE_DOUBLE(*((_QWORD *)p + 3) ^ 0x8000000000000000LL) * q[3]
     + COERCE_DOUBLE(*((_QWORD *)p + 2) ^ 0x8000000000000000LL) * q[2]
     + *p * *q
     - p[1] * q[1];
  r[1] = COERCE_DOUBLE(*((_QWORD *)p + 3) ^ 0x8000000000000000LL) * q[2] + p[2] * q[3] + p[1] * *q + *p * q[1];
  r[2] = COERCE_DOUBLE(*((_QWORD *)p + 1) ^ 0x8000000000000000LL) * q[3] + p[3] * q[1] + p[2] * *q + *p * q[2];
  r[3] = COERCE_DOUBLE(*((_QWORD *)p + 2) ^ 0x8000000000000000LL) * q[1] + p[1] * q[2] + p[3] * *q + *p * q[3];
}