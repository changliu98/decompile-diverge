int rand_r(unsigned int *seed) {
  *seed = *seed * 1103515245 + 12345;
  return ((*seed) >> 16) & 0x7fff;
}