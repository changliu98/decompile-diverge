bool func0(int dict[], int size, int n) {
  for (int i = 0; i < size; i++) {
    if (dict[i] != n) {
      return false;
    }
  }
  return true;
}