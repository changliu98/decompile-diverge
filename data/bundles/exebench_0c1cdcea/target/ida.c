void __cdecl TriggsM(double *filter, double *M)
{
  double a3; // [rsp+0h] [rbp-30h]
  double a2; // [rsp+8h] [rbp-28h]
  double a1; // [rsp+10h] [rbp-20h]
  double scale; // [rsp+18h] [rbp-18h]

  a3 = *filter;
  a2 = filter[1];
  a1 = filter[2];
  scale = 1.0 / ((a1 + 1.0 - a2 + a3) * (1.0 - a1 - a2 - a3) * ((a1 - a3) * a3 + a2 + 1.0));
  *M = scale
     * (COERCE_DOUBLE(*(_QWORD *)filter ^ 0x8000000000000000LL) * *filter
      + COERCE_DOUBLE(*(_QWORD *)filter ^ 0x8000000000000000LL) * a1
      + 1.0
      - a2);
  M[1] = scale * (a3 + a1) * (a3 * a1 + a2);
  M[2] = scale * a3 * (a3 * a2 + a1);
  M[3] = scale * (a3 * a2 + a1);
  M[4] = -scale * (a2 - 1.0) * (a3 * a1 + a2);
  M[5] = -scale * a3 * (a3 * a1 + a3 * a3 + a2 - 1.0);
  M[6] = scale * (COERCE_DOUBLE(*(_QWORD *)&a2 ^ 0x8000000000000000LL) * a2 + a1 * a1 + a3 * a1 + a2);
  M[7] = scale
       * (COERCE_DOUBLE(*(_QWORD *)&a3 ^ 0x8000000000000000LL) * a2
        + -(a3 * a3) * a3
        + -(a1 * a3) * a3
        + a1 * a2
        + a3 * a2 * a2
        + a3);
  M[8] = scale * a3 * (a3 * a2 + a1);
}