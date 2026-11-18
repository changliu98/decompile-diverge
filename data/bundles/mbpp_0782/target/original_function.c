int func0(int arr[], int l) {
  int Sum = 0;
  for (int i = 0; i < l; i++) {
    Sum += ((((i + 1) * (l - i) + 1) / 2) * arr[i]);
  }
  return Sum;
}