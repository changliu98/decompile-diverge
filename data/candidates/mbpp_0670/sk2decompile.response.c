bool _is_sorted(int* array, int size) {
  int i;
  for (i = 0; i < size - 1; i++) {
    if (array[i] >= array[i + 1]) {
      return false;
    }
  }
  return true;
}