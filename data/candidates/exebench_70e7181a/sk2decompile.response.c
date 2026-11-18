void split(int i, int i1, int i2, int j1, int *i1p, int *i2p, int *j1p,
           int *j2p, int n) {
  int n1 = i2 - i + 1;
  if (n1 > 0) {
    *i1p = i1;
    *i2p = i1 + n / n1 - 1;
    *j1p = i1 + n / n1;
    *j2p = j1;
  }
}