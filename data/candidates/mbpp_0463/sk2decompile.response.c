int func0(int A[], int n) {
  int max = 1, min = 1, result = 0, flag = 0;
  int i;
  for (i = 0; i < n; i++) {
    if (A[i] > 0) {
      max = max * A[i];
      min = (min * A[i] < 1) ? min * A[i] : 1;
      flag = 1;
    } else if (A[i] == 0) {
      max = 1;
      min = 1;
    } else {
      int tmp = max;
      max = (min * A[i] > 1) ? min * A[i] : 1;
      min = tmp * A[i];
    }
    if (result < max) result = max;
  }
  if (flag == 0 && result == 0) return 0;
  return result;
}