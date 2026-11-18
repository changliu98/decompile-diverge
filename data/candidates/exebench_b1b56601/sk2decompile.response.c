void nexper(int n, int *a, int *more, int *swaps) {
  int i, j, k, l, m, count, temp, sum, n1, n2;
  if (*more == 0) {
    for (i = 1; i <= n; i++) a[i] = i;
    *more = 1;
    *swaps = 1;
    return;
  }
  if (*swaps == 1) {
    temp = a[1];
    a[1] = a[2];
    a[2] = temp;
    *swaps = 0;
    if (a[n] == 1 && a[1] == n % 2 + 2) {
      if (n < 4) {
        *more = 0;
        return;
      }
      for (i = 1; i <= n - 3; i++) {
        if (a[i + 1] != a[i] + 1) return;
      }
      *more = 0;
    }
    return;
  }
  sum = 0;
  for (i = 2; i <= n; i++) {
    temp = a[i];
    n1 = i - 1;
    n2 = 1;
    count = 0;
    while (n2 <= n1) {
      if (a[n2] > temp) count++;
      n2++;
    }
    sum += count;
    if (count != sum % 2 * n1) {
      k = (sum + 1) % 2 * (n + 1);
      for (j = 1; j <= n1; j++) {
        l = a[j] - temp;
        m = a[j] - k;
        if ((l >= 0 && m < 0) || (l < 0 && m >= 0)) {
          k = a[j];
          l = j;
        }
      }
      a[l] = temp;
      a[i] = k;
      *swaps = 1;
      return;
    }
  }
  *more = 0;
}