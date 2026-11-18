void swap2(int *x,int *y)
{
  *x ^= *y;
  *y ^= *x;
  *x ^= *y;
}