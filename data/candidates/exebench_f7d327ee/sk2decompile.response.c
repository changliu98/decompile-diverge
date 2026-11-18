unsigned t_add(unsigned a, unsigned b, int *no_overflow) {
  unsigned result;
  *no_overflow = *no_overflow && (a <= b ? b : a) >= a + b;
  result = *no_overflow ? a + b : 0;
  return result;
}