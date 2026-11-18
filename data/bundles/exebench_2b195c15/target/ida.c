void __cdecl swap(long *xp, long *yp)
{
  long t0; // [rsp+8h] [rbp-18h]

  t0 = *xp;
  *xp = *yp;
  *yp = t0;
}