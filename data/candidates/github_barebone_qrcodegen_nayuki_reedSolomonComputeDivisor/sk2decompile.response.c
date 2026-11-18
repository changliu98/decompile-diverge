void reedSolomonComputeDivisor(int degree, uint8_t divisor[]) {
  int i, j;
  uint8_t x;
  ((void)((1 <= degree && degree <= 30) ||
          (_assert("1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX",
                   "func.c", 362,
                   "void reedSolomonComputeDivisor(int, uint8_t *)"),
           0)));
  memset(divisor, 0, (unsigned int)degree);
  divisor[degree - 1] = 1;
  x = 1;
  for (j = 0; j < degree; j++) {
    for (i = 0; i < degree; i++) {
      divisor[i] = reedSolomonMultiply(divisor[i], x);
      if (i + 1 < degree) {
        divisor[i] ^= divisor[i + 1];
      }
    }
    x = reedSolomonMultiply(x, 2);
  }
}