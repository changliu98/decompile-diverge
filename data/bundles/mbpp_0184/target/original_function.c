bool func0(int list[], int count, int num) {
  for (int i = 0; i < count; i++) {
    if (list[i] < num) {
      return false;
    }
  }
  return true;
}