int f1(int x, int *y)
{
  *y = x & 0x5f;
  return x;
}