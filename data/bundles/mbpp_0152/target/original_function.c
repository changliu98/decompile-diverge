void func0(int arr[], int len) {
  if (len < 2) {
    return;
  }
  int mid = len / 2;
  int *left = (int *)malloc(mid * sizeof(int));
  int *right = (int *)malloc((len - mid) * sizeof(int));
  for (int i = 0; i < mid; i++) {
    left[i] = arr[i];
  }
  for (int i = mid; i < len; i++) {
    right[i - mid] = arr[i];
  }
  func0(left, mid);
  func0(right, len - mid);
  merge(left, mid, right, len - mid, arr);
  free(left);
  free(right);
}