int func0(int *a, int n) {
  int max = 0;
  int i, j, count, temp;
  for (j = 0; j < n - 1; j++) {
    for (i = 0; i < n - j - 1; i++) {
      if (a[i] > a[i + 1]) {
        temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
      }
    }
  }
  for (i = 0; i < n; i++) {
    count = 1;
    while (i + 1 < n && a[i] == a[i + 1]) {
      i++;
      count++;
    }
    if (count > max) max = count;
  }
  return max;
}