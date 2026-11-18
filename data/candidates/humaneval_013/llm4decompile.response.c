int func0(int a, int b)
{
  while (b) {
    a = a % b;
    b = a;
  }

  return a;
}