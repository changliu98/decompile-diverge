int func0(int *arr, int n) {
  int res = 1;
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
  for (int i = 0; i < n; i++) {
    if (i == 0 || arr[i - 1] != arr[i]) {
      res *= arr[i];
    }
  }
  return res;
}