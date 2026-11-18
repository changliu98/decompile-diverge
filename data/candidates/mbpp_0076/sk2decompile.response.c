int _sum_of_squares(int a, int b) {
  int tmp, sum_of_squares_a, sum_of_squares_b;
  if (b < a) {
    tmp = b;
    b = a;
    a = tmp;
  }
  sum_of_squares_a = a * (a + 1) * (2 * a + 1) / 6;
  sum_of_squares_b = a * (a + 1) * (b - a) / 2;
  return sum_of_squares_a + sum_of_squares_b;
}