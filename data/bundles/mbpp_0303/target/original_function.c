int func0(int a[], int n) {
  int mx = INT_MIN;
  for (int j = 1; j < n; j++) {
    if (mx > a[j]) {
      return 0;
    }
    if (a[j - 1] > mx) {
      mx = a[j - 1];
    }
  }
  return 1;
}