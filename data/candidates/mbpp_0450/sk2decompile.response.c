char **func0(char **arr, int n, int len, int *ret) {
  int i, j = 0;
  for (i = 0; i < n; i++) {
    if (strlen(arr[i]) == len) {
      ret_arr[j++] = arr[i];
    }
  }
  *ret = j;
  return ret_arr;
}