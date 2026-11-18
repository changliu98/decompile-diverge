int func0(int list[], int size) {
  int res = 0;
  for (int i = 0; i < size; i++) {
    res = res * 10 + list[i];
  }
  return res;
}