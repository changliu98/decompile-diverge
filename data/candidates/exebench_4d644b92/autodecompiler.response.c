int twiddle1(int *x, int *y)
{
  *x = *x + *y;
  *x = *x + *y;
  return *x;
}