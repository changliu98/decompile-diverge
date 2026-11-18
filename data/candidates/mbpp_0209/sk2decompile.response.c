void func0(int *arr, int n, int k, int *res) {
  buildHeap(arr, n);
  if (arr[0] <= k) {
    arr[0] = k;
    heapify(arr, n, 0);
    for (int i = 0; i < n; i++) {
      res[i] = arr[i];
    }
  }
}