void _counting_sort(int *array, int size) {
  int max = 0;
  for (int i = 0; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }
  int *count = malloc(sizeof(int) * (max + 1));
  for (int i = 0; i <= max; i++) {
    count[i] = 0;
  }
  for (int i = 0; i < size; i++) {
    count[array[i]]++;
  }
  int index = 0;
  for (int i = 0; i <= max; i++) {
    for (int j = 0; j < count[i]; j++) {
      array[index] = i;
      index++;
    }
  }
  free(count);
}