double Mat_doubleSwap(double *d) {
  union {
    double d;
    unsigned char c[8];
  } u;
  u.d = *d;
  unsigned char t = u.c[0];
  u.c[0] = u.c[7];
  u.c[7] = t;
  t = u.c[1];
  u.c[1] = u.c[6];
  u.c[6] = t;
  t = u.c[2];
  u.c[2] = u.c[5];
  u.c[5] = t;
  t = u.c[3];
  u.c[3] = u.c[4];
  u.c[4] = t;
  *d = u.d;
  return *d;
}