int func0(int *a, int n, int k) {
  int max = a[0];
  int res = 0;
  int i;
  for (i = 1; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }
  for (i = 0; i < n; i++) {
    if ((max - a[i]) % k != 0) {
      return -1;
    }
    res += (max - a[i]) / k;
  }
  return res;
}