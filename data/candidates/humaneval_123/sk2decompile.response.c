void func0(int n, int *arr, int *size) {
  int *a = arr;
  int max = 10;
  *size = 1;
  a[0] = 1;
  while (n != 1) {
    if (n % 2 == 1) {
      if (*size >= max) {
        max *= 2;
        a = realloc(a, max * sizeof(int));
      }
      a[(*size)++] = n;
      n = 3 * n + 1;
    } else {
      n /= 2;
    }
  }
  int i, j, key;
  for (i = 1; i < *size; i++) {
    key = a[i];
    j = i - 1;
    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = key;
  }
}