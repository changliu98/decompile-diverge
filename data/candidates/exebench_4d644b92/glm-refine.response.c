int __cdecl twiddle1(int *xp, int *yp)
{
  int y_val = *yp;
  *xp += 2 * y_val;
  return *xp;
}