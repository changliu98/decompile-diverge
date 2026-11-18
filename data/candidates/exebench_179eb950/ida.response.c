void __cdecl swap_int(int *x, int *y)
{
  *y ^= *x;
  *x ^= *y;
  *y ^= *x;
}