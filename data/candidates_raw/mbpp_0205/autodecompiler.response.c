void test_not(int *tup, int len, int *res) {
  for(int i = 0; i < len; i++) {
    res[i] = ~tup[i];
  }
}