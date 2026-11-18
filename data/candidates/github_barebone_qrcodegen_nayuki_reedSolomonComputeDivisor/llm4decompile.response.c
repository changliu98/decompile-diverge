void reedSolomonComputeDivisor(int degree, uint8_t *result) {
 if (!(1 <= degree && degree <= 30)) { __assert_fail("1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX", "func.c", 362, "void reedSolomonComputeDivisor(int, uint8_t *)"); };

 memset(result, 0, (size_t)degree);
 result[degree - 1] = 1;

 uint8_t root = 1;
 for (int i = 0; i < degree; i++) {
  for (int j = 0; j < degree; j++) {
   result[j] = reedSolomonMultiply(result[j], root);
   if (j + 1 < degree)
    result[j] ^= result[j + 1];
  }
  root = reedSolomonMultiply(root, 2);
 }
}