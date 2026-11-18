int func0(int *arr, int n) {
  int i, j, temp;
  for (j = 0; j < n; j++) {
    for (i = j + 1; i < n; i++) {
      if (arr[j] > arr[i]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  for (j = n - 1; j >= 0; j--) {
    if (is_palindrome(arr[j])) {
      return arr[j];
    }
  }
  return -1;
}