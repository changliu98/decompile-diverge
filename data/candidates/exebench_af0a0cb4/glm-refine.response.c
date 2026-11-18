// Swaps the values of two integers pointed to by x and y.
void __cdecl std::swap<int>(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}