void __shellsort(int *a, int n) {
  int v, j, h, i;
  for (h = n / 2; h > 0; h /= 2) {
    for (i = h; i < n; i++) {
      v = a[i];
      j = i;
      while (j >= h && a[j - h] > v) {
        a[j] = a[j - h];
        j -= h;
      }
      a[j] = v;
    }
  }
}