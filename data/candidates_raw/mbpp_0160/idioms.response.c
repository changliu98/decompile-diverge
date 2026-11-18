char *solve(int a, int b, int n)
{
  int x = 0;
  while (a * x <= n) {
    int y = n - a * x;
    if (y % b == 0) {
      sprintf(result, "x = %d, y = %d", x, y / b);
      return result;
    }
    x++;
  }
  return "No solution";
}