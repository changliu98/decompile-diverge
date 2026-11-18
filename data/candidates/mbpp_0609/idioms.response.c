int func0(int a, int b, int n)
{
  int i;
  if (n < b - 1)
    i = b - 1;
  else
    i = n;
  return a * i / b;
}