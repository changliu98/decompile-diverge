int func0(int x) {
  if (x == 0) return 1;
  int x1 = x + 1;
  int x2 = x1 & x;
  if (x2 == 0) return x;
  int x3 = log2((double)x2) + 1;
  int x4 = 1 << (x3 - 1);
  return x | x4;
}