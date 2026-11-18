int __ffs(int i) {
  int j;
  j = (int)(log2((double)(-i & i)) + 1.0);
  return j;
}