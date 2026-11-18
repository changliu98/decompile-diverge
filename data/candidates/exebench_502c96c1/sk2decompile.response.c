void encipher(unsigned long *numbers, unsigned long *sums) {
  unsigned long v0, v1, i, k;
  v0 = numbers[0];
  v1 = numbers[1];
  i = 0;
  for (k = 0; k < 31; k++) {
    i += 0x9E3779B1;
    v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (i + sums[i & 3]);
    i += 0x9E3779B1;
    v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (i + sums[i >> 11 & 3]);
  }
  numbers[0] = v0;
  numbers[1] = v1;
}