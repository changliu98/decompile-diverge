int func0(int n)
{
  int result;

  if (n == 0)
    result = 1;
  else if (n < 3)
    result = n;
  else if (n == 3)
    result = 6;
  else if (n == 4)
    result = 4;
  else
    result = 0;

  return result;
}