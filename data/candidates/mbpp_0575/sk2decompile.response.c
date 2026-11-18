int func0(int a, int b, int c, int d) {
  int count = 0;
  for (int i = c; i <= d; i++) {
    if (i % a != 0) {
      count++;
    }
    if (count == b) {
      break;
    }
  }
  return c;
}