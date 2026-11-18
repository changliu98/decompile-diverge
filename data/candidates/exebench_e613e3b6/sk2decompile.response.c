int cal_intervals(int *a, int *b, int n) {
  int i, j, k = 0;
  for (i = 0; i < n && a[i] == 0; i++)
    ;
  while (i < n) {
    while (i < n && a[i] != 0) i++;
    j = 0;
    while (i < n && a[i] == 0) {
      i++;
      j++;
    }
    if (i < n) {
      b[k] = j;
      k++;
    }
  }
  return k + 1;
}