int func0(int n) {
  int i, flag = 0;
  for (i = 2; i <= (int)sqrt((double)n); i++) {
    if (n % i == 0) flag = 1;
  }
  return flag;
}