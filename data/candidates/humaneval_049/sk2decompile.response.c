int func0(int a, int b) {
  int i, r = 1;
  for (i = 0; i < a; i++) {
    r = (r * 2) % b;
  }
  return r;
}