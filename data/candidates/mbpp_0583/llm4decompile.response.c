int func0(int n)
{
  int i;
  int result;

  if (n < 2) {
    return 1;
  }

  result = 0;
  for (i = 0; i < n; i++) {
    result += func0(i) * func0(n - i - 1);
  }

  return result;
}