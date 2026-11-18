int func0(int arr[], int n) {
  int odd = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] % 2) {
      odd += 1;
    }
  }
  if (odd % 2) {
    return 1;
  }
  return 2;
}