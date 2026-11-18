int func0(int a) {
  int b = a;
  char c = 0;
  if (a != 0 && (a & (a - 1)) == 0) return a;
  while (b != 0) {
    b >>= 1;
    c++;
  }
  return 1 << c;
}