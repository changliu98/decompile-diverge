float *_filter_positive(float *arr, int len, int *new_len) {
  float *new_arr = malloc(len * sizeof(float));
  *new_len = 0;
  for (int i = 0; i < len; i++) {
    if (arr[i] > 0) {
      new_arr[(*new_len)++] = arr[i];
    }
  }
  return new_arr;
}