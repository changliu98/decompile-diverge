int func0(int n) {
  int i = 0;
  while (n) {
    n /= 10;
    i++;
  }
  return i;
}