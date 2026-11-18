int func0(int n)
{
  int ret;
  double tmp;

  tmp = get_sum(n);
  if (n < tmp)
    ret = 1;
  else
    ret = 0;

  return ret;
}