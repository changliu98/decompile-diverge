int _sum_of_squares(int a, int b) {
  if (b < a) {
    int t = a;
    a = b;
    b = t;
  }
  return (a + 1) * (b + 1) * (3 * a - b + 1) / 6;
}