static size_t div10quickm(size_t* bits) {
  size_t n = *bits;
  size_t s = 0;
  size_t m = n >> 1;
  size_t h = m >> 2;
  m += h;
  s += h;
  h = m >> 4;
  m += h;
  s += h;
  h = m >> 8;
  m += h;
  s += h;
  h = m >> 16;
  m += h;
  s += h;
  h = m >> 32;
  m += h;
  s += h;
  s = (s + 1) >> 1;
  n -= (m - s) << 1;
  *bits = n;
  return n;
}