double func0(double *arr, int size) {
  if (size < 2) {
    return -9999999;
  }
  int dup = 0;
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (arr[j] == arr[i]) {
        dup++;
        break;
      }
    }
  }
  if (size == 2 && dup == 1) {
    return -9999999;
  }
  double *temp = malloc(size * sizeof(double));
  int temp_size = 0;
  for (int i = 0; i < size; i++) {
    int found = 0;
    for (int j = 0; j < temp_size; j++) {
      if (temp[j] == arr[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      temp[temp_size++] = arr[i];
    }
  }
  for (int i = 0; i < temp_size; i++) {
    for (int j = i + 1; j < temp_size; j++) {
      if (temp[i] > temp[j]) {
        double t = temp[i];
        temp[i] = temp[j];
        temp[j] = t;
      }
    }
  }
  double result = temp[1];
  free(temp);
  return result;
}