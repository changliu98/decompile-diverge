void func0(int arr[], int n, int result[]) {
  qsort(arr, n, sizeof(int), cmpfunc);
  for (int i = 0; i < n; i++) {
    result[i] = arr[i];
  }
}