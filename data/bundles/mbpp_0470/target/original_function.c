void func0(const int test_tup[], int size, int result[]) {
  for (int i = 0; i < size - 1; i++) {
    result[i] = test_tup[i] + test_tup[i + 1];
  }
}