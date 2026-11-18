bool func0(int* a, int a_size, int* b, int b_size) {
  bool hash[1000];
  memset(hash, 0, sizeof(hash));
  for (int i = 0; i < a_size; i++) {
    hash[a[i]] = true;
  }
  for (int i = 0; i < b_size; i++) {
    if (!hash[b[i]]) {
      return false;
    }
  }
  return true;
}