int n_to_n2(int n)
{
  int n2 = (int)(floor(sqrt((double)n)) + 1);
  return n2 * n2;
}