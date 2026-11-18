int func0(int a) {
  int i, j, k;
  j = 0;
  k = 0;
  for (i = a; i > 0; i >>= 1) {
    if (j % 2 == 0) k |= 1 << j;
    j++;
  }
  k |= a;
  return k;
}