double _n_choose_3(int n) {
  double result;
  result = (n + 2) * (n + 1) * n;
  result /= 6.0;
  return result;
}