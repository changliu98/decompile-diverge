void _radix_sort(int* array, int size) {
  int exp = 1;
  int max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }
  int* temp = (int*)malloc(size * sizeof(int));
  int* count = (int*)malloc(10 * sizeof(int));
  while (max >= exp) {
    for (int i = 0; i < 10; i++) {
      count[i] = 0;
    }
    for (int i = 0; i < size; i++) {
      int index = (array[i] / exp) % 10;
      count[index]++;
    }
    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
      int index = (array[i] / exp) % 10;
      temp[count[index] - 1] = array[i];
      count[index]--;
    }
    for (int i = 0; i < size; i++) {
      array[i] = temp[i];
    }
    exp *= 10;
  }
  free(temp);
  free(count);
}