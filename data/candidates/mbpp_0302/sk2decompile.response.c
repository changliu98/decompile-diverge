int func0(int n) {
  if (n == 0) return 0;
  int i = 0;
  int j = n / 2;
  while (j > 0) {
    i++;
    j /= 2;
  }
  return 1 << i;
}