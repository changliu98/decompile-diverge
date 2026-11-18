int func0(int arr[], int n) {
  int sum = 0;
  for (int i = n - 1; i >= 0; --i) {
    sum += i * arr[i] - (n - 1 - i) * arr[i];
  }
  return sum;
}