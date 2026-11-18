int *_get_unique_values(int *values, int values_size, int *unique_values,
                        int unique_values_size, int *unique_values_size_ptr) {
  int *unique_values_ptr = malloc(values_size * sizeof(int));
  int unique_values_size_local = 0;
  for (int i = 0; i < values_size; i++) {
    int found = 0;
    for (int j = 0; j < unique_values_size_local; j++) {
      if (unique_values_ptr[j] == values[i]) {
        found = 1;
        break;
      }
    }
    if (found == 0) {
      for (int k = 0; k < unique_values_size; k++) {
        if (values[i] == unique_values[k]) {
          unique_values_ptr[unique_values_size_local++] = values[i];
          break;
        }
      }
    }
  }
  for (int i = 0; i < unique_values_size_local - 1; i++) {
    for (int k = 0; k < unique_values_size_local - i - 1; k++) {
      if (unique_values_ptr[k] > unique_values_ptr[k + 1]) {
        int temp = unique_values_ptr[k];
        unique_values_ptr[k] = unique_values_ptr[k + 1];
        unique_values_ptr[k + 1] = temp;
      }
    }
  }
  *unique_values_size_ptr = unique_values_size_local;
  return unique_values_ptr;
}