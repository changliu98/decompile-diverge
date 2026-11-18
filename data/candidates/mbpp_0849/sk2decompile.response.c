int func0(int n) {
  int sum, i, j;
  int arr[n + 1];
  for (i = 0; i <= n; i++) arr[i] = 0;
  for (i = 2; i <= n; i++) {
    if (arr[i] == 0) {
      for (j = i; j <= n; j += i) arr[j] += i;
    }
  }
  return arr[n];
}