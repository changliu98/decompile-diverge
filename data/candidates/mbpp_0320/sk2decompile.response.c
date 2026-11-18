int _problem0006(int n) {
  int i, sum_of_squares, sum;
  sum_of_squares = 0;
  sum = 0;
  for (i = 1; i <= n; i++) {
    sum_of_squares += i * i;
    sum += i;
  }
  return sum * sum - sum_of_squares;
}