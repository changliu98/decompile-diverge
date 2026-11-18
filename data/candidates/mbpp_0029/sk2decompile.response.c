int _find_odd_occurring(int *arr, int size) {
  int i, j, count;
  for (i = 0; i < size; i++) {
    count = 0;
    for (j = 0; j < size; j++) {
      if (arr[i] == arr[j]) count++;
    }
    if (count % 2 != 0) return arr[i];
  }
  return -1;
}