int func0(int n) {
  int fact = 1;
  for (int i = 2; i <= n; i++) {
    fact = fact * i;
    while (fact % 10 == 0) {
      fact = fact / 10;
    }
  }
  while (fact >= 10) {
    fact = fact / 10;
  }
  return floor(fact);
}