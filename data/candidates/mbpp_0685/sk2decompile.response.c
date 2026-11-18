int func0(int n) {
  char arr[n + 1];
  for (int i = 0; i <= n; i++) {
    arr[i] = 1;
  }
  for (int j = 2; j * j <= n; j++) {
    if (arr[j] == 1) {
      for (int i = j * 2; i <= n; i += j) {
        arr[i] = 0;
      }
    }
  }
  int sum = 0;
  for (int i = 2; i <= n; i++) {
    if (arr[i] != 0) {
      sum += i;
    }
  }
  return sum;
}