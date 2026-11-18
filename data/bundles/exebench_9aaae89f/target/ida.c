void __cdecl pick(int *np, int *nr)
{
  if ( ++*nr >= 768 )
  {
    ++*np;
    *nr = 0;
  }
  if ( *np >= 180 )
    *np = 0;
}