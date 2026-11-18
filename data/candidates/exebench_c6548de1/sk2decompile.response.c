void swap(int *a) {
  int min, i, max;
  min = 0;
  for (i = 0; i < 10; i++) {
    if (a[i] < a[0]) {
      min = i;
    }
  }
  max = 0;
  for (i = 0; i < 10; i++) {
    if (a[i] > a[0]) {
      max = i;
    }
  }
  a[0] = a[0] + a[min];
  a[min] = a[0] - a[min];
  a[0] = a[0] - a[min];
  a[9] = a[9] + a[max];
  a[max] = a[9] - a[max];
  a[9] = a[9] - a[max];
}