int *_max_array(int *array, int size) {
  int *max_array;
  int i;
  int max;
  if (size <= 0) return NULL;
  max_array = malloc(size * sizeof(int));
  if (max_array == NULL) return NULL;
  max = array[0];
  for (i = 0; i < size; i++) {
    if (array[i] > max) max = array[i];
    max_array[i] = max;
  }
  return max_array;
}