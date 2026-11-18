int func0(int n) {
  int p = 1;
  int flag = 0;
  while (n > 0) {
    if (n % 10 % 2 == 1) {
      flag = 1;
      p *= n % 10;
    }
    n /= 10;
  }
  if (flag)
    return p;
  else
    return 0;
}