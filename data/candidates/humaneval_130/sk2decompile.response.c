int* func0(int n) {
  int* ret = malloc(sizeof(int) * (n + 1));
  ret[0] = 1;
  if (n == 0) return ret;
  ret[1] = 3;
  for (int i = 2; i <= n; i++) {
    ret[i] = i % 2 == 0 ? i / 2 + 1 : (i + 1) / 2 + ret[i - 2] + ret[i - 1] + 1;
  }
  return ret;
}