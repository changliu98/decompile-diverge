void __cdecl set_stimulus(unsigned __int8 *dst, char *p)
{
  while ( *p )
  {
    if ( *p >= 48 && *p <= 55 )
      *dst &= ~(1 << (*p - 48));
    ++p;
  }
}