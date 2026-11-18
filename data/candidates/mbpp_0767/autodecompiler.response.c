int func0(int a[], int n, int x) {
  int i, j;
  int ans = 0;

  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      if (a[i] + a[j] == x)
        ans++;
    }
  }

  return ans;
}