void Swap8Bytes(unsigned char *p) {
  unsigned char t;
  t = p[0];
  p[0] = p[7];
  p[7] = t;
  t = p[1];
  p[1] = p[6];
  p[6] = t;
  t = p[2];
  p[2] = p[5];
  p[5] = t;
  t = p[3];
  p[3] = p[4];
  p[4] = t;
}