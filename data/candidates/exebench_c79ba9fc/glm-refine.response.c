void __cdecl swap(int *x, int *y)
{
  if (x && y)
  {
    int temp = *x;
    *x = *y;
    *y = temp;
  }
}