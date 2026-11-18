short g(int *a, short *b) {
  short c = *b;
  *a = 10;
  return c;
}