void __cdecl swap_int(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}