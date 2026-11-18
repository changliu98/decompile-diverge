int func0(int arr[], int n) {
  int ans = 0, count = 0;
  int i, j;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  int *v = (int *)malloc(n * sizeof(int));
  int size_v = 0;
  v[size_v++] = arr[0];
  for (i = 1; i < n; i++) {
    if (arr[i] != arr[i - 1]) {
      v[size_v++] = arr[i];
    }
  }
  for (i = 0; i < size_v; i++) {
    if (i > 0 && v[i] == v[i - 1] + 1) {
      count++;
    } else {
      count = 1;
    }
    if (ans < count) {
      ans = count;
    }
  }
  free(v);
  return ans;
}