void __cdecl iw_restrict_to_range(int r1, int r2, int *pvar)
{
  if ( *pvar >= r1 )
  {
    if ( *pvar > r2 )
      *pvar = r2;
  }
  else
  {
    *pvar = r1;
  }
}