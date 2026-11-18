int func0(int x, int y)
{
  if (y < 0)
    return -func0(x, -y);
  else if (y == 0)
    return 0;
  else if (y == 1)
    return x;
  else
    return x + func0(x, y - 1);
}