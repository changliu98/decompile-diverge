int func0(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[i] < arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  int num = arr[0];
  for (int i = 1; i < n; i++) {
    num = num * 10 + arr[i];
  }
  return num;
}