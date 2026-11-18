bool _has_zero(int *array, int size) {
  int i;
  for (i = 0; i < size; i++) {
    if (array[i] == 0) {
      return true;
    }
  }
  return false;
}