void bmp_iter_next(unsigned int *bitmap, int *bit) {
  *bitmap >>= 1;
  *bit += 1;
  return;
}