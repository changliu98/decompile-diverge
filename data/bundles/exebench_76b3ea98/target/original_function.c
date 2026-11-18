void swap_ints(int *i, int *j)
{
  int temp;

  temp = *i;
  *i = *j;
  *j = temp;

  return;
}