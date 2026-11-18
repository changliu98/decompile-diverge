int func0(int a, int b) {
  int gcd = ngcd(a, b);
  int count = 0;
  int sqrt_gcd = (int)sqrt((double)gcd);
  for (int i = 1; i <= sqrt_gcd; i++) {
    if (gcd % i == 0) {
      count += 2;
      if (i == gcd / i) {
        count--;
      }
    }
  }
  return count;
}