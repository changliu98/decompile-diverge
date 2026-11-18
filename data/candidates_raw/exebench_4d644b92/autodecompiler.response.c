int fun(int *x, int *y)
{
  *x = *x + *y;
  *x = *x + *y;
  return *x;
}