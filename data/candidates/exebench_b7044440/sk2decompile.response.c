void shiftarray(int array[]) {
  int i;
  for (i = 0; i < 10 - 1; i++) {
    array[i] = array[i + 1];
  }
  array[10 - 1] = -1;
}