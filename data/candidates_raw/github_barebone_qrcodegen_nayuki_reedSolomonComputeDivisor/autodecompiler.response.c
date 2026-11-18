void reedSolomonComputeDivisor(int degree, unsigned char *div) {
 do { if (!(1 <= degree && degree <= 30)) ___assert_fail("1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX", "./func.c", 362, "void reedSolomonComputeDivisor(int, uint8_t *)"); } while (0);
 memset(div, 0, (size_t)(degree << 0));
 div[degree - 1] = 1;
 unsigned char root = 1;
 for (int i = 0; ; i++) {
  if (i >= degree)
   return;
  for (int j = 0; ; j++) {
   if (j >= degree)
    break;
   div[j] = reedSolomonMultiply(div[j], root);
   if (j + 1 < degree)
    div[j + 1] ^= div[j];
  }
  root = reedSolomonMultiply(root, 0x02);
 }
}