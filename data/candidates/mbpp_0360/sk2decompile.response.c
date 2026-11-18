int _get_max_index(int n) {
  double nd;
  int n2;
  nd = pow(2.0, (double)n);
  n2 = (int)(nd - 1.0);
  return n2 * n2 - 2;
}