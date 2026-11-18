int func0(int n) {
  int m = n;
  int result = 0;
  int i = 0;
  for (int j = m; j > 0; j >>= 1) {
    if (i % 2 == 1) {
      result |= 1 << i;
    }
    i++;
  }
  return n ^ result;
}