int test_and_set(int *one)
{
  int ret = *one;
  *one = 1;
  return ret;
}