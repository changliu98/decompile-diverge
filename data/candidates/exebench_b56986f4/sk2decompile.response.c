void makeipt(int n, int *ipt) {
  int i, n1, n2, i1;
  ipt[2] = 0;
  ipt[3] = 16;
  n1 = 2;
  while (n > 32) {
    n2 = n1 * 2;
    for (i1 = n1; i1 < n2; i1++) {
      i = ipt[i1] * 4;
      ipt[i1 + n1] = i;
      ipt[i1 + n2] = i + n1 * 16;
    }
    n1 = n2;
    n >>= 2;
  }
}