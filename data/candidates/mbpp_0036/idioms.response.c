int func0(int a, int b, int n)
{
  int res;
  while (n > 0) {
    --n;
    a = a * 10;
    res = a / b;
    a = a % b;
  }
  return (res);
}