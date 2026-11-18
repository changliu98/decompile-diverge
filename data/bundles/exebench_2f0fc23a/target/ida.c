void __cdecl next(int *i, int *j, int p)
{
  if ( ++*j == p )
  {
    *j = 0;
    ++*i;
  }
}