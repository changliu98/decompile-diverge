int gcd_ptr(int *a, int *b) {
  int *temp;
  while (*a > 0) {
    if (*a < *b) {
      temp = a;
      a = b;
      b = temp;
    }
    *a -= *b;
  }
  return *b;
}