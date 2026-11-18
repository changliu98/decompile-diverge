int func0(int L, int R) {
  int count = 0;
  for (int i = L; i <= R; i++) {
    if (i >= 10 && i <= 15) {
      count++;
    } else if (i > 15) {
      int k = i;
      while (k != 0) {
        if (k % 16 >= 10) {
          count++;
        }
        k = k / 16;
      }
    }
  }
  return count;
}