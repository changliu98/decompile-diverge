void __cdecl h(int *x, int y)
{
  *x = (*x <= y) ? *x - y : (h(x, *x), *x);
}