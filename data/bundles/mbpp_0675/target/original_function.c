int func0(int x, int y, int m, int n) {
  int sum_nums = x + y;
  if (sum_nums >= m && sum_nums <= n) {
    return 20;
  } else {
    return sum_nums;
  }
}