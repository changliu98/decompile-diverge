float modff(float x, float *iptr) {
  int e;
  unsigned m;
  union {
    float f;
    unsigned u;
  } u;
  e = ((*(unsigned *)&x) >> 23 & 0xff) - 0x7f;
  if (e >= 23) {
    *iptr = x;
    if (e == 0x80 && (*(unsigned *)&x << 9)) return x;
    return (*(unsigned *)&x) & 0x80000000;
  }
  if (e < 0) {
    *iptr = (*(unsigned *)&x) & 0x80000000;
    return x;
  }
  m = 0x7fffff >> e;
  if (((*(unsigned *)&x) & m) == 0) {
    *iptr = x;
    return (*(unsigned *)&x) & 0x80000000;
  }
  u.u = (*(unsigned *)&x) & ~m;
  *iptr = u.f;
  return x - u.f;
}