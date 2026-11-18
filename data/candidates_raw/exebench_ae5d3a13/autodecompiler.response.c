void array_sum(double *arr, int n, double *res) {
  double sum = 0;
  int i;
  for (i = 0; i < n; i++) {
    sum += arr[i];
  }
  *res = sum;
}