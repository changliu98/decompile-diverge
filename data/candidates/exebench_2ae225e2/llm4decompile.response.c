void make_double_bigendian(double *x)
{
  anon_union_8_2_94730023 u;
  unsigned char *p;
  u.d = *x;
  p = (unsigned char *) &u.d;
  *x = ((double) (((unsigned long) p[0] << 56) |
     ((unsigned long) p[1] << 48) |
     ((unsigned long) p[2] << 40) |
     ((unsigned long) p[3] << 32) |
     ((unsigned long) p[4] << 24) |
     ((unsigned long) p[5] << 16) |
     ((unsigned long) p[6] << 8) |
     ((unsigned long) p[7])));
}