int _numTrees(int n) {
  if (n <= 1) {
    return 1;
  }
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += _numTrees(i) * _numTrees(n - i - 1);
  }
  return sum;
}