int func0(int *arr, int n) {
  int count, i, j, max = 0;
  int max_num = arr[0];
  for (j = 0; j < n; j++) {
    count = 0;
    for (i = 0; i < n; i++) {
      if (arr[i] == arr[j]) {
        count++;
      }
    }
    if (count > max) {
      max = count;
      max_num = arr[j];
    }
  }
  return max_num;
}