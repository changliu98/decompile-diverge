int Fibonacci_search(int *a, int n, int key) {
  int f[13] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
  int k = 0;
  int value = 0;
  int i = 0;
  int low = 0;
  int mid = 0;
  k = n;
  value = key;
  i = 0;
  low = n;
  while (f[i] - 1 < k) {
    i++;
  }
  for (mid = k; mid < f[i] - 1; mid++) {
    a[mid] = a[k];
  }
  while (low <= k) {
    mid = low + f[i - 1] - 1;
    if (a[mid] > value) {
      i--;
      low = low - f[i] + 1;
    } else if (a[mid] < value) {
      low = low + f[i - 1];
      i = i - 2;
    } else {
      if (mid <= k) {
        return mid;
      } else {
        return low - 1;
      }
    }
  }
  return 0;
}