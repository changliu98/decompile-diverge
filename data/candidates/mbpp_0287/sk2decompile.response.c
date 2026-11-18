int _n_cells(int n) {
  int nc;
  nc = (n + 1) * (n + 1) * (2 * n + 1) * (2 * n);
  nc /= 3;
  return nc;
}