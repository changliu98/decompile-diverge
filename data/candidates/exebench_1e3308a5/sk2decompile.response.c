void neg_s(float *a, float *b) {
  int c;
  c = *a;
  c ^= 0x80000000;
  *b = c;
}