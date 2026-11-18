int func0(int a, int b) {
  int c = abs(a - b);
  int sum = 0;
  while (c > 0) {
    sum += c % 10;
    c /= 10;
  }
  return sum;
}