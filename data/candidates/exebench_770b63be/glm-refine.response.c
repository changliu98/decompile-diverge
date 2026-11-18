void __cdecl decrease_order(int *num1, int *diff)
{
  if (*num1 < *diff)
  {
    int tmp = *num1;
    *num1 = *diff;
    *diff = tmp;
  }
}