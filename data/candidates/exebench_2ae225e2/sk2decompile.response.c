void make_double_bigendian(double *d) {
  union {
    double d;
    unsigned char c[8];
  } u;
  u.c[0] = (unsigned char)((*d) >> 56);
  u.c[1] = (unsigned char)((*d) >> 48);
  u.c[2] = (unsigned char)((*d) >> 40);
  u.c[3] = (unsigned char)((*d) >> 32);
  u.c[4] = (unsigned char)((*d) >> 24);
  u.c[5] = (unsigned char)((*d) >> 16);
  u.c[6] = (unsigned char)((*d) >> 8);
  u.c[7] = (unsigned char)(*d);
  *d = u.d;
}