char* func0(int a, int b, int n) {
  int i = 0;
  static char result[50];
  while (i * a <= n) {
    if ((n - (i * a)) % b == 0) {
      sprintf(result, "x = %d, y = %d", i, (n - (i * a)) / b);
      return result;
    }
    i++;
  }
  return "No solution";
}