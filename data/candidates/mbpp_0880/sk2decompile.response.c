char* _solve_quadratic_equation(int a, int b, int c) {
  int delta = b * b - 4 * a * c;
  if (delta > 0) {
    return "2 solutions";
  } else if (delta == 0) {
    return "1 solution";
  } else {
    return "No solutions";
  }
}