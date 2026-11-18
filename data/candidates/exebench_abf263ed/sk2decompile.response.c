void ZVdotU22(int n, double *A, double *B, double *C, double *D, double *res) {
  double r0, r1, r2, r3, r4, r5, r6, r7, a0r, a1i, b0r, b1i, c0r, c1i;
  int i, j, j2;
  r0 = 0.0;
  r1 = 0.0;
  r2 = 0.0;
  r3 = 0.0;
  r4 = 0.0;
  r5 = 0.0;
  r6 = 0.0;
  r7 = 0.0;
  i = 0;
  j = 0;
  j2 = 1;
  for (; j < n; j++, i += 2, j2 += 2) {
    a0r = A[i];
    a1i = A[j2];
    b0r = B[i];
    b1i = B[j2];
    c0r = C[i];
    c1i = C[j2];
    r4 = r4 + a0r * c0r - a1i * c1i;
    r5 = r5 + a0r * c1i + a1i * c0r;
    r6 = r6 + a0r * b0r - a1i * b1i;
    r7 = r7 + a0r * b1i + a1i * b0r;
    r0 = r0 + b0r * c0r - b1i * c1i;
    r1 = r1 + b0r * c1i + b1i * c0r;
    r2 = r2 + b0r * r4 - b1i * r5;
    r3 = r3 + b0r * r5 + b1i * r4;
  }
  res[0] = r4;
  res[1] = r5;
  res[2] = r6;
  res[3] = r7;
  res[4] = r0;
  res[5] = r1;
  res[6] = r2;
  res[7] = r3;
}