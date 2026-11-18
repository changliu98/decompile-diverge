int max(float *arr) {
  int max_index = 0;
  float max_value = arr[0];
  for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
    if (arr[i] > max_value) {
      max_index = i;
      max_value = arr[i];
    }
  }
  return max_index;
}