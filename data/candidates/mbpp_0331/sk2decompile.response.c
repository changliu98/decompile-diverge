int func0(int n) {
  int count = 0;
  int i = 1;
  while (i < n + 1) {
    if ((n & i) == 0) {
      count++;
    }
    i = i << 1;
  }
  return count;
}