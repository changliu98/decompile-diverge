int func0(int a, int b, int d) {
  int temp = a;
  a = a < b ? a : b;
  b = temp > b ? temp : b;
  if (d >= b) {
    return (d + b - 1) / b;
  }
  if (d == 0) {
    return 0;
  }
  if (d == a) {
    return 1;
  }
  return 2;
}