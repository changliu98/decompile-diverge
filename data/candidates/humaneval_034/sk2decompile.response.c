int *_get_unique_values(int *values, int size, int *unique_size) {
  int *unique_values = malloc(size * sizeof(int));
  int unique_values_size = 0;
  for (int i = 0; i < size; i++) {
    int found = 0;
    for (int j = 0; j < unique_values_size; j++) {
      if (values[i] == unique_values[j]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      unique_values[unique_values_size++] = values[i];
    }
  }
  for (int i = 0; i < unique_values_size - 1; i++) {
    for (int j = i + 1; j < unique_values_size; j++) {
      if (unique_values[i] > unique_values[j]) {
        int temp = unique_values[i];
        unique_values[i] = unique_values[j];
        unique_values[j] = temp;
      }
    }
  }
  *unique_size = unique_values_size;
  return unique_values;
}