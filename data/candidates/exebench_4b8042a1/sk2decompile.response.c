int next_arr_seq(int *arr, int n, int max) {
  int i;
  for (i = 0; i < n; i++) {
    arr[i]++;
    if (arr[i] <= max) {
      return 1;
    } else {
      arr[i] = 0;
    }
  }
  return 0;
}