void __cdecl inplace_swap(int *x, int *y)
{
  *y ^= *x;
  *x ^= *y;
  *y ^= *x;
}