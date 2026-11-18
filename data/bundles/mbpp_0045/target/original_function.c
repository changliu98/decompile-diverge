int func0(int *l, int size) {
  int num1 = l[0];
  int num2 = l[1];
  int gcd = find_gcd(num1, num2);
  for (int i = 2; i < size; i++) {
    gcd = find_gcd(gcd, l[i]);
  }
  return gcd;
}