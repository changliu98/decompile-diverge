int func0(int n, int k) {
  int arr[n];
  int j = 0;
  for (int i = 1; i <= n; i += 2) {
    arr[j] = i;
    j++;
  }
  for (int i = 2; i <= n; i += 2) {
    arr[j] = i;
    j++;
  }
  return arr[k - 1];
}