int func0(int a, int b, int c) {
  int d;
  if (b - 1 < c) {
    d = b - 1;
  } else {
    d = c;
  }
  return a * d / b;
}