int get_max_pos(int n)
{
  int max = (int) pow(2.0, (double) n) - 1;
  return (max * max - 2);
}