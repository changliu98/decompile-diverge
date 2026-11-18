int func0(int x, int y) {
  int n = ngcd(x, y);
  int result = 0;
  int z = (int)sqrt(n);
  int i = 1;
  while (i <= z) {
    if (n % i == 0) {
      result += 2;
      if (i == n / i) {
        result -= 1;
      }
    }
    i++;
  }
  return result;
}