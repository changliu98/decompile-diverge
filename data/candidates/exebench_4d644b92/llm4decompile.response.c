int
twiddle1 (volatile int *xp, int *yp)
{
  *xp += *yp;
  *xp += *yp;
  return *xp;
}