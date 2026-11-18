int func0(int n) {
  int sum = 0;
  int i = 0;
  while (n != 0) {
    sum += (n % 10) * pow(2.0, (double)i);
    n /= 10;
    i++;
  }
  return sum;
}