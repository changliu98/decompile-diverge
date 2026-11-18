bool __all(bool *array, int size) {
  int i;
  for (i = 0; i < size; i++) {
    if (!array[i]) {
      return false;
    }
  }
  return true;
}