static unsigned int sgl_len(unsigned int n) {
  unsigned int len;
  len = (n - 1) * 3 / 2;
  len += (n - 1) & 1;
  len += 2;
  return len;
}