void func0(int arr[], int n) {
  int next_pos = -1, i;
  for (i = 0; i < n; i++) {
    if (next_pos >= 0 && ((arr[i] >= 0 && arr[next_pos] < 0) ||
                          (arr[i] < 0 && arr[next_pos] >= 0))) {
      right_rotate(arr, n, next_pos, i);
      if (i - next_pos >= 3)
        next_pos += 2;
      else
        next_pos = -1;
    }
    if (next_pos == -1 && ((arr[i] >= 0 && i % 2 == 0) ||
                           (arr[i] < 0 && i % 2 == 1)))
      next_pos = i;
  }
}