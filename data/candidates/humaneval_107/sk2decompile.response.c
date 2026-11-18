int* func0(int n) {
  int* result = malloc(2 * sizeof(int));
  result[0] = 0;
  result[1] = 0;
  for (int i = 1; i <= n; i++) {
    int reverse = 0;
    int temp = i;
    while (temp != 0) {
      reverse = reverse * 10 + temp % 10;
      temp /= 10;
    }
    if (i == reverse) {
      if (i % 2 == 0) {
        result[0]++;
      } else {
        result[1]++;
      }
    }
  }
  return result;
}