int func0(int x)
{
  int fact = 1;
  int i;
  for (i = 1; i < x; i++) {
    fact *= i;
    if (fact % x == 0)
      break;
  }
  return i;
}