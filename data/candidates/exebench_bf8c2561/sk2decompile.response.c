double readDummyArray(double *array, unsigned long size) {
  unsigned long n = size / sizeof(double);
  unsigned long i;
  double sum = 0.0;
  for (i = 0; i < n; i++) {
    sum += array[i];
  }
  array[0] = sum / n;
  return sum;
}