int func0(int n) {
  int i;
  for (i = 0; i * i * i <= abs(n); i++) {
    if (i * i * i == abs(n)) {
      return 1;
    }
  }
  return 0;
}