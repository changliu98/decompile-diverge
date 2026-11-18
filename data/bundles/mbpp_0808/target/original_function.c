bool func0(int test_tup[], int n, int K) {
  bool res = false;
  for (int i = 0; i < n; i++) {
    if (test_tup[i] == K) {
      res = true;
      break;
    }
  }
  return res;
}