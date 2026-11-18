int func0(int arr[], int n) {
  int size = n;
  return find_peak_util(arr, 0, size - 1, size);
}