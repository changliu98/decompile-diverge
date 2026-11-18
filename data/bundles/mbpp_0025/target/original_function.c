int func0(int arr[], int n) {
  int i, j, temp, prod = 1;
  for (i = 1; i < n; i++) {
    temp = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > temp) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = temp;
  }
  for (i = 0; i < n; i++) {
    if (i == 0 || arr[i - 1] != arr[i]) {
      prod *= arr[i];
    }
  }
  return prod;
}