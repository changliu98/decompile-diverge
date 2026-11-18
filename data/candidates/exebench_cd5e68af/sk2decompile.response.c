void merge(int a[], int b[], int c[]) {
  int i = 0, j = 0, k = 0;
  while (i < 6 && j < 6) {
    if (a[i] < b[j])
      c[k++] = a[i++];
    else
      c[k++] = b[j++];
  }
  while (i < 6) c[k++] = a[i++];
  while (j < 6) c[k++] = b[j++];
}