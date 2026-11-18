bool _is_heap(int *arr, int n, int i) {
  if (2 * i + 2 > n) return true;
  bool left = arr[i] <= arr[2 * i + 1] && _is_heap(arr, n, 2 * i + 1);
  bool right = n == 2 * i + 2 ||
               (arr[i] <= arr[2 * i + 2] && _is_heap(arr, n, 2 * i + 2));
  return left && right;
}