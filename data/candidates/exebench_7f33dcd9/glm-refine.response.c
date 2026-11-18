void __cdecl std::swap<int>(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}