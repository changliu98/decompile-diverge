int getPossibleCount(int *possible, int *value) {
  int count = 0;
  int i;
  for (i = 0; i < 9; i++) {
    if (possible[i] != 0) {
      count++;
      *value = possible[i];
    }
  }
  return count;
}