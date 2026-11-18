void __heapify(int *a, int n) {
  int i, j, t;
  for (i = n / 2 - 1; i >= 0; i--) {
    j = 2 * i + 1;
    while (j < n) {
      if (j + 1 < n && a[j] > a[j + 1]) j++;
      if (a[i] <= a[j]) break;
      t = a[i];
      a[i] = a[j];
      a[j] = t;
      i = j - 1;
      j = 2 * i + 1;
    }
  }
}