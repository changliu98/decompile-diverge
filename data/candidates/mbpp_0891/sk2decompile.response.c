bool __isZero(int a, int b) {
  while (a > 0 && b > 0) {
    a /= 10;
    b /= 10;
  }
  return a == 0 && b == 0;
}