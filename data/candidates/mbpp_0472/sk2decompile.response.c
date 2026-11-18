bool _is_consecutive(int *arr, int len) {
  int *sorted = malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    sorted[i] = arr[i];
  }
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (sorted[i] > sorted[j]) {
        int tmp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = tmp;
      }
    }
  }
  bool is_consecutive = true;
  for (int i = 1; i < len; i++) {
    if (sorted[i] != sorted[i - 1] + 1) {
      is_consecutive = false;
      break;
    }
  }
  free(sorted);
  return is_consecutive;
}