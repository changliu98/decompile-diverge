void max_ptr(int *a, int *b) {
  if (*a > *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
  }
}