double func0(int nums[], int n) {
  int n1 = 0;
  for (int i = 0; i < n; i++) {
    if (nums[i] > 0) {
      n1 += 1;
    }
  }
  double result = ((double)n1 / n);
  result = round(result * 100) / 100;
  return result;
}