void __cdecl swap(int *xp, int *yp)
{
  *xp += *yp;
  *yp = *xp - *yp;
  *xp -= *yp;
}