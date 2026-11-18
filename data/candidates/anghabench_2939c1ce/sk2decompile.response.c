void swapIntEndian(unsigned char *p) {
  unsigned char t;
  t = p[0];
  p[0] = p[3];
  p[3] = t;
  t = p[1];
  p[1] = p[2];
  p[2] = t;
}