bool _is_sorted(int *array, int size, int start) {
  int i;
  for (i = 0; i < size; i++) {
    if (array[i] < start) {
      return false;
    }
  }
  return true;
}