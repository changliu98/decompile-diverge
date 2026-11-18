int and_peep2_qi(int x, int *y)
{
  *y = x & 0x5f;
  return x;
}