int func0(int a, int b, int c) {
  int d;
  if (c < b - 1)
    d = b - 1;
  else
    d = c;
  return a * d / b;
}