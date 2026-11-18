int foo(int *a, int *b, int c) {
  *a *= 2;
  *b /= 2;
  return *a + *b;
}