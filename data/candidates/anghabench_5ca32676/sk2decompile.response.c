static void wht4x4(int16_t *coef) {
  int i, a0, a1, a2, a3, t0;
  for (i = 0; i < 4; i++) {
    a0 = coef[i];
    a1 = coef[i + 4];
    a2 = coef[i + 8];
    a3 = coef[i + 12];
    t0 = a0 + a1;
    a0 = t0 - a2;
    a1 = t0 - a3;
    a2 = a0 >> 1;
    a3 = a1 >> 1;
    a0 -= a2;
    a1 -= a3;
    coef[i] = t0 - a1;
    coef[i + 4] = a1;
    coef[i + 8] = a2 + a3;
    coef[i + 12] = a2;
  }
  for (i = 0; i < 4; i++) {
    a0 = coef[i * 4];
    a1 = coef[i * 4 + 1];
    a2 = coef[i * 4 + 2];
    a3 = coef[i * 4 + 3];
    t0 = a0 + a1;
    a0 = t0 - a2;
    a1 = t0 - a3;
    a2 = a0 >> 1;
    a3 = a1 >> 1;
    a0 -= a2;
    a1 -= a3;
    coef[i * 4] = t0 - a1 << 1;
    coef[i * 4 + 1] = a1 << 1;
    coef[i * 4 + 2] = a2 + a3 << 1;
    coef[i * 4 + 3] = a2 << 1;
  }
}