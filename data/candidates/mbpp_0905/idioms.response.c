int func0(int n, int r){
  int res = factorial(n + 1, 2 * n);
  res = res / factorial(1, n);
  return res;
}