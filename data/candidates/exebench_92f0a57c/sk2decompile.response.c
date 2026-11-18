double HTS_rnd(unsigned long *seed) {
  *seed = *seed * 1103515245 + 12345;
  return (double)(*seed & 0x7fff) / 32767.0;
}