void func0(int *arr, int n) {
  int max_index;
  while (n > 1) {
    max_index = find_max_index(arr, n);
    if (max_index != n - 1) {
      reverse(arr, 0, max_index);
      reverse(arr, 0, n - 1);
    }
    n--;
  }
}