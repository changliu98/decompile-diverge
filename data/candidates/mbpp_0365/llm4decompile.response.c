int func0(int n)
{
  int count;
  for (count = 0; n != 0; count++)
    n /= 10;
  return count;
}