void __cdecl innerdct(const double *a, double *b, const double *c)
{
  double b5; // [rsp+0h] [rbp-48h]
  double b4; // [rsp+8h] [rbp-40h]
  double b3; // [rsp+10h] [rbp-38h]
  double b3a; // [rsp+10h] [rbp-38h]
  double b2; // [rsp+18h] [rbp-30h]
  double b2a; // [rsp+18h] [rbp-30h]
  double b1; // [rsp+20h] [rbp-28h]
  double b1a; // [rsp+20h] [rbp-28h]
  double b0; // [rsp+28h] [rbp-20h]
  double b0a; // [rsp+28h] [rbp-20h]

  b2 = *a + a[7];
  b3 = a[1] + a[6];
  b4 = a[2] + a[5];
  b5 = a[3] + a[4];
  b0 = (b2 + b5) * c[4];
  b1 = (b3 + b4) * c[4];
  *b = b0 + b1;
  b[32] = b0 - b1;
  b[16] = (b2 - b5) * c[2] + (b3 - b4) * c[6];
  b[48] = (b2 - b5) * c[6] + (b4 - b3) * c[2];
  b0a = *a - a[7];
  b1a = a[1] - a[6];
  b2a = a[2] - a[5];
  b3a = a[3] - a[4];
  b[8] = b3a * c[7] + b2a * c[5] + b0a * c[1] + b1a * c[3];
  b[24] = COERCE_DOUBLE(*(_QWORD *)&b3a ^ 0x8000000000000000LL) * c[5]
        + COERCE_DOUBLE(*(_QWORD *)&b2a ^ 0x8000000000000000LL) * c[1]
        + b0a * c[3]
        - b1a * c[7];
  b[40] = b3a * c[3] + b2a * c[7] + b0a * c[5] - b1a * c[1];
  b[56] = COERCE_DOUBLE(*(_QWORD *)&b3a ^ 0x8000000000000000LL) * c[1] + b2a * c[3] + b0a * c[7] - b1a * c[5];
}