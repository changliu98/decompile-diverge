int _n_triangles(int n) {
  int n_tri;
  n_tri = (n + 1) * n * (2 * n + 1);
  n_tri /= 6;
  return n_tri;
}