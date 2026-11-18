void __cdecl std::swap<int>(int *x, int *y)
{
  int tmp = *x;
  *x = *y;
  *y = tmp;
}