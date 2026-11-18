int func0(int num[], int size) {
  int count_elim = 0;
  for (int i = 0; i < size; i++) {
    if (num[i] == -1) {
      break;
    }
    count_elim++;
  }
  return count_elim;
}