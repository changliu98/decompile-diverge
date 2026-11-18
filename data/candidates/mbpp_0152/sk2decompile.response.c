void _merge_sort(int *arr, int len) {
  if (len < 2) return;
  int len_left = len / 2;
  int len_right = len - len_left;
  int *left = malloc(len_left * sizeof(int));
  int *right = malloc(len_right * sizeof(int));
  for (int i = 0; i < len_left; i++) left[i] = arr[i];
  for (int i = len_left; i < len; i++) right[i - len_left] = arr[i];
  _merge_sort(left, len_left);
  _merge_sort(right, len_right);
  merge(left, len_left, right, len_right, arr);
  free(left);
  free(right);
}