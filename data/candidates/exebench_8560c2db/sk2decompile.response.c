unsigned int mc_bitcode(float *data, float threshold) {
  unsigned int bitcode = 0;
  unsigned int i;
  for (i = 0; i < 8; i++) {
    if (data[i] > threshold) {
      bitcode |= 1 << i;
    }
  }
  return bitcode;
}