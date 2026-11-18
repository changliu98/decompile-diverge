void raw_relu_bulk_apply_function(int size, float *data) {
  int i;
  for (i = 0; i < size; ++i) {
    data[i] = (data[i] > 0) ? data[i] : 0;
  }
}