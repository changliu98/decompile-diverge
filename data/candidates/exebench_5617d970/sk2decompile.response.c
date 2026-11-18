int arrayFind(int value, int *array, int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    if (array[i] == value) {
      for (j = 0; j < i; j++) {
        array[i - j] = array[i - j - 1];
      }
      array[0] = value;
      return 0;
    }
  }
  return -1;
}