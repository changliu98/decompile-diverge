char *__cdecl get_mod_and_div(long *mod, long *div, char *toa, long n)
{
  char *toaa; // [rsp+8h] [rbp-18h]

  toaa = toa;
  if ( n >= 0 )
  {
    *mod = n % 10;
    *div = n / 10;
  }
  else
  {
    *mod = -(n % 10);
    *div = n / -10;
    *toa = 45;
    return toa + 1;
  }
  return toaa;
}