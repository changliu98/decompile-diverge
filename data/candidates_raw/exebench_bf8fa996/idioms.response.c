int get_and_set_one(int *one)
{
  int ret = *one;
  *one = 1;
  return ret;
}