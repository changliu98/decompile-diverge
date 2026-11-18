void reedSolomonComputeDivisor(int degree, unsigned char *divisor)
{
  ((void) sizeof ((1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX) ? 1 : 0), __extension__ ({ if (1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX) ; else __assert_fail ("1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX", "func.c", 362, __extension__ __PRETTY_FUNCTION__); }));
  reedSolomonSetAll(divisor, 0, degree);
  divisor[degree - 1] = 1;
  unsigned char root = 1;
  for (int i = 0; i < degree; i++) {
    for (int j = 0; j < degree; j++) {
      divisor[j] = multiply(divisor[j], root);
      if (j + 1 < degree)
        divisor[j] ^= divisor[j + 1];
    }
    root = multiply(root, 2);
  }
}