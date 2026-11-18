int func0(int a, int b) {
  int c = a ^ b;
  int d = c >> 31;
  d = !d;
  return d;
}