int func0(int A, int N, int L, int R) {
  int count = 0;
  int i;
  for (i = L; i <= R; i++) {
    if (i % A != 0) {
      count += 1;
    }
    if (count == N) {
      break;
    }
  }
  return i;
}