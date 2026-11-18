int func0(int n) {
  if (n == 0)
    return 0;
  else
    return n % 10 + func0(n / 10);
}