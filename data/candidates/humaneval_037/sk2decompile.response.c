void _sort_even_odd(float *data, int size, float *out) {
  float *even = malloc((size / 2 + 1) * sizeof(float));
  int even_size = 0;
  for (int i = 0; i < size; i += 2) {
    even[even_size++] = data[i];
  }
  for (int i = 0; i < even_size - 1; i++) {
    for (int j = 0; j < even_size - i - 1; j++) {
      if (even[j] > even[j + 1]) {
        float temp = even[j];
        even[j] = even[j + 1];
        even[j + 1] = temp;
      }
    }
  }
  for (int i = 0; i < size; i++) {
    out[i] = i % 2 == 0 ? even[i / 2] : data[i];
  }
  free(even);
}