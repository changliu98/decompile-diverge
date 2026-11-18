int
f(int *x, int *y, int z)
{
  *x <<= 1;
  *y /= 2;
  z = *x + *y;
  return z;
}