int func0(int a, int b) {
  int c;
  c = sum_Odd(b);
  c -= sum_Odd(a - 1);
  return c;
}