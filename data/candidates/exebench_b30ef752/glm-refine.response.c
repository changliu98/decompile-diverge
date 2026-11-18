void __cdecl limit2_u16(unsigned __int16 *x, unsigned __int16 lower, unsigned __int16 upper)
{
  if (*x < upper)
  {
    if (*x <= lower)
      *x = lower;
  }
  else
  {
    *x = upper;
  }
}