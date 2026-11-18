int __cdecl swap(int *x, int *y)
{
  int tmp; // [rsp+0h] [rbp-14h]

  tmp = *x;
  *x = *y;
  *y = tmp;
  return 0;
}