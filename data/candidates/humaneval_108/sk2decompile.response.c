int func0(int *a, int n) {
  int i, j, k, count;
  count = 0;
  for (i = 0; i < n; i++) {
    if (a[i] > 0) {
      count++;
    } else {
      k = 0;
      j = abs(a[i]);
      while (j >= 10) {
        k += j % 10;
        j /= 10;
      }
      if (k - j > 0) {
        count++;
      }
    }
  }
  return count;
}