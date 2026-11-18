int __cdecl swap(int *x, int *y)
{
  int tmp = *x;
  *x = *y;
  *y = tmp;
  
  return 0;
}