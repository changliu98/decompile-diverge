void func0(int n, int *a) {
  int even = 0, odd = 0, m;
  m = abs(n);
  do {
    if (m % 10 % 2 == 0)
      even++;
    else
      odd++;
    m /= 10;
  } while (m > 0);
  a[0] = even;
  a[1] = odd;
}