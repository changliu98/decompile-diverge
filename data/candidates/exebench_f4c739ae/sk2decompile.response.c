double randum(long *seed) {
  long s, s1, s2, s3, s4, s5;
  double r;
  s = *seed & 0x0fff;
  s1 = (1549 * s) & 0x0fff;
  s2 = (1549 * s) >> 12;
  s3 = (1549 * (s >> 12)) & 0x0fff;
  s4 = (1549 * (s >> 12)) >> 12;
  s5 = (s + (406 * s) + (13 * (s >> 12)) + s2 + s3 + s4) & 0x0fff;
  s2 = (s + (406 * s) + (13 * (s >> 12)) + s2 + s3 + s4) >> 12;
  s3 = (s + (406 * s) + (13 * (s >> 12)) + s2 + s3 + s4) >> 24;
  *seed = (s1 << 12) | s5 | (s3 << 24);
  r = (double)s1 / 4096.0 + (double)s5 / 4096.0 / 4096.0 +
      (double)s3 / 4096.0 / 4096.0 / 4096.0;
  return r;
}