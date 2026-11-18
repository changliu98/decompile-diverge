float median(float *array, int n) {
  int i, j;
  float temp;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (array[i] > array[j]) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
  if (n % 2 == 1) {
    return array[n / 2];
  } else {
    return (array[n / 2] + array[n / 2 - 1]) / 2.0;
  }
}