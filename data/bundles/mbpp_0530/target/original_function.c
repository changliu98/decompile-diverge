double func0(int nums[], int n) {
  int n1 = 0;
  for (int i = 0; i < n; i++) {
    if (nums[i] < 0) n1++;
  }
  double result = ((double)n1) / n;
  return round(result * 100) / 100;
}