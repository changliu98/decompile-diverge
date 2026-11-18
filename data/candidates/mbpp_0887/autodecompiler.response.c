int func0(int n)
{
  char c;
  if ((n ^ 1) == (n - 1))
    c = 1;
  else
    c = 0;

  return c & 1;
}