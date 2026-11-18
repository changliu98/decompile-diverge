int func0(int a[], int n) {
  int i = 0, sum = 0, leftsum = 0;
  for (i = 0; i < n; i++) sum += a[i];
  for (i = 0; i < n; i++) {
    sum -= a[i];
    if (leftsum == sum) return i;
    leftsum += a[i];
  }
  return -1;
}